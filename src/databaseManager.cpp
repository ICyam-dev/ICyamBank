#include "header/databaseManager.h"
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QSqlError>
#include <QObject>
#include <QMessageBox>
#include <QHash>

// Initialisation de la variable statique
// Static variable initialization
int databaseManager::currentFolderId = -1;  // -1 signifie qu'aucun dossier n'est sélectionné / -1 means no folder is selected

// **Méthodes de gestion du dossier en cours / Current Folder Management Methods**
int databaseManager::getCurrentFolderId() {
    return currentFolderId;
}

void databaseManager::setCurrentFolderId(int folderId) {
    currentFolderId = folderId;
}

// **Chemins de fichiers et gestion des documents / File Paths and Document Management**
QString databaseManager::getDatabasePath() {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString dbDirectory = documentsPath + "/ICyamBank";
    return dbDirectory + "/ICyamBank.db";
}

QString databaseManager::getHashFilePath() {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString hashDirectory = documentsPath + "/ICyamBank";
    QString hashFilePath = hashDirectory + "/db_hash";
    return hashFilePath;
}

// **Fonctions de hashage / Hashing Functions**
QString databaseManager::generateHashFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QObject::tr("Erreur : Impossible d'ouvrir le fichier pour générer le hash.") << filePath;
        return QString();
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);
    if (hash.addData(&file)) {
        return QString(hash.result().toHex());
    }

    return QString();
}

bool databaseManager::saveHashToFile(const QString &hash) {
    QString hashFilePath = getHashFilePath();
    QFile file(hashFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de sauvegarder le fichier hash.") << hashFilePath;
        return false;
    }

    QTextStream out(&file);
    out << hash;
    return true;
}

QString databaseManager::loadHashFromFile() {
    QString hashFilePath = getHashFilePath();
    QFile file(hashFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de lire le fichier hash.") << hashFilePath;
        return QString();
    }

    QTextStream in(&file);
    return in.readAll().trimmed();
}

// **Configuration de la base de données / Database Setup**
bool databaseManager::setupDatabase() {
    QString dbPath = getDatabasePath();

    QDir dir;
    if (!dir.exists(QFileInfo(dbPath).path())) {
        if (!dir.mkpath(QFileInfo(dbPath).path())) {
            qDebug() << QObject::tr("Erreur : Impossible de créer le répertoire ICyamBank.");
            return false;
        }
    }

    QString documentsDirectory = QFileInfo(dbPath).path() + "/_docs";
    if (!dir.exists(documentsDirectory)) {
        if (!dir.mkpath(documentsDirectory)) {
            qDebug() << QObject::tr("Erreur : Impossible de créer le répertoire 'documents'.");
            return false;
        }
    }

    bool databaseJustCreated = false;

    if (!QFile::exists(dbPath)) {
        if (!QFile::copy(":/database/ICyamBank.db", dbPath)) {
            qDebug() << QObject::tr("Erreur : Échec de la copie de la base de données vierge.");
            return false;
        }
        databaseJustCreated = true;

        QString initialHash = generateHashFromFile(dbPath);
        if (!initialHash.isEmpty() && !saveHashToFile(initialHash)) {
            return false;
        }

        QFile::setPermissions(dbPath, QFileDevice::WriteOwner | QFileDevice::ReadOwner);
    }

    QSqlDatabase db = QSqlDatabase::database("ICyamBankConnection");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE", "ICyamBankConnection");
        db.setDatabaseName(dbPath);
    }

    if (!db.open()) {
        qDebug() << QObject::tr("Erreur : Impossible d'ouvrir la base de données SQLite.") << db.lastError().text();
        return false;
    }

    if (databaseJustCreated) {
        insertDefaultAccountTypes();
        databaseManager dbManager;
        dbManager.insertDefaultUser();
    }

    return true;
}

// **Méthodes de gestion de la désactivation et de la suppression / Soft Delete and Deactivation**
bool databaseManager::deactivateBank(int bankId) {
    QSqlQuery query;
    query.prepare("UPDATE bank SET is_active = 0 WHERE id_bank = :id");
    query.bindValue(":id", bankId);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la désactivation de la banque:" << query.lastError().text();
        return false;
    }
    return true;
}

bool databaseManager::deactivateAccountsForBank(int bankId) {
    QSqlQuery query;
    query.prepare("UPDATE account SET is_active = 0 WHERE id_bank = :id");
    query.bindValue(":id", bankId);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la désactivation des comptes pour la banque:" << query.lastError().text();
        return false;
    }
    return true;
}

// **Méthodes pour insérer des données par défaut / Methods to Insert Default Data**
void databaseManager::insertDefaultAccountTypes()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name='type_account'");
    if (!query.exec() || !query.next()) {
        qDebug() << QObject::tr("Erreur : La table 'type_account' n'existe pas.");
        return;
    }

    query.prepare("INSERT INTO type_account (name_type, description) VALUES (:name_type, :description)");

    struct AccountType {
        QString name;
        QString description;
    };

    QList<AccountType> accountTypes = {
        {QObject::tr("Dépôt"), QObject::tr("Comptes de dépôt pour les transactions quotidiennes.")},
        {QObject::tr("Épargnes"), QObject::tr("Comptes d'épargne pour accumuler des fonds.")},
        {QObject::tr("Dettes"), QObject::tr("Comptes pour gérer les dettes.")},
        {QObject::tr("Portefeuilles"), QObject::tr("Comptes pour gérer des actifs financiers.")},
        {QObject::tr("Biens"), QObject::tr("Comptes pour gérer des biens matériels.")}
    };

    for (const AccountType &accountType : accountTypes) {
        query.bindValue(":name_type", accountType.name);
        query.bindValue(":description", accountType.description);
        query.exec();
    }
}

void databaseManager::insertDefaultUser()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name='user'");
    if (!query.exec() || !query.next()) {
        qDebug() << QObject::tr("Erreur : La table 'user' n'existe pas.");
        return;
    }

    query.prepare("INSERT INTO user (first_name, last_name, email, phone, address, default_currency) "
                  "VALUES (:first_name, :last_name, :email, :phone, :address, :default_currency)");
    query.bindValue(":first_name", QObject::tr("Utilisateur"));
    query.bindValue(":last_name", QObject::tr("Inconnu"));
    query.bindValue(":default_currency", QObject::tr("EUR"));
    query.exec();
}

// **Méthodes pour obtenir les derniers IDs insérés / Methods to Retrieve Last Inserted IDs**
int databaseManager::getLastInsertedBankId() {
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.exec("SELECT MAX(id_bank) FROM bank WHERE is_deleted = 0");
    return query.next() ? query.value(0).toInt() : -1;
}

int databaseManager::getLastInsertedGroupId() {
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.exec("SELECT MAX(id_group) FROM group_account WHERE is_deleted = 0");
    return query.next() ? query.value(0).toInt() : -1;
}
