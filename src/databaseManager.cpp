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
#include <QMessageBox>  // Ajout pour les messages pop-up // Added for pop-up messages
#include <QHash>

                      QString databaseManager::getDatabasePath() {
    // Récupérer le chemin des documents utilisateurs
    // Get the path of the user's documents
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString dbDirectory = documentsPath + "/ICyamBank";
    return dbDirectory + "/ICyamBank.db";
}

QString databaseManager::getHashFilePath() {
    // Récupérer le chemin du fichier hash
    // Get the path of the hash file
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString hashDirectory = documentsPath + "/ICyamBank";
    QString hashFilePath = hashDirectory + "/db_hash";

    // Vérification du chemin de fichier
    // Verify the file path
    qDebug() << "Chemin du fichier hash:" << hashFilePath;  // Debug path

    return hashFilePath;
}

QString databaseManager::generateHashFromFile(const QString &filePath) {
    // Générer un hash SHA256 à partir du contenu d'un fichier
    // Generate a SHA256 hash from the contents of a file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QObject::tr("Erreur : Impossible d'ouvrir le fichier pour générer le hash.") << filePath;  // Affiche également le chemin du fichier // Also displays the file path
        return QString();
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);  // Utiliser l'algorithme SHA256 // Using SHA256 algorithm
    if (hash.addData(&file)) {
        return QString(hash.result().toHex());  // Retourner le hash sous forme de chaîne hexadécimale // Return the hash as a hexadecimal string
    }

    return QString();
}

bool databaseManager::saveHashToFile(const QString &hash) {
    // Sauvegarder le hash dans un fichier
    // Save the hash to a file
    QString hashFilePath = getHashFilePath();

    QFile file(hashFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de sauvegarder le fichier hash.") << hashFilePath;  // Affiche également le chemin du fichier // Also displays the file path
        return false;
    }

    QTextStream out(&file);
    out << hash;

    qDebug() << QObject::tr("Hash sauvegardé avec succès.") << hashFilePath;  // Ajout d'un message pour confirmer la sauvegarde // Added a message to confirm the save
    return true;
}

QString databaseManager::loadHashFromFile() {
    // Charger le hash sauvegardé à partir du fichier
    // Load the saved hash from the file
    QString hashFilePath = getHashFilePath();

    QFile file(hashFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de lire le fichier hash.") << hashFilePath;  // Affiche également le chemin du fichier // Also displays the file path
        return QString();
    }

    QTextStream in(&file);
    QString hash = in.readAll().trimmed();

    qDebug() << QObject::tr("Hash chargé avec succès.") << hashFilePath;  // Ajout d'un message pour confirmer le chargement // Added a message to confirm the loading
    return hash;
}

bool databaseManager::setupDatabase() {
    QString dbPath = getDatabasePath();

    // Créer le répertoire s'il n'existe pas
    QDir dir;
    if (!dir.exists(QFileInfo(dbPath).path())) {
        if (!dir.mkpath(QFileInfo(dbPath).path())) {
            qDebug() << QObject::tr("Erreur : Impossible de créer le répertoire ICyamBank.");
            return false;
        }
    }

    // Cas où la base de données n'existe pas
    if (!QFile::exists(dbPath)) {
        // 1. Copier la base de données depuis les ressources
        if (!QFile::copy(":/database/ICyamBank.db", dbPath)) {
            qDebug() << QObject::tr("Erreur : Échec de la copie de la base de données vierge.");
            return false;
        }
        qDebug() << QObject::tr("Base de données vierge copiée avec succès.");

        // 2. Générer le hash de la base copiée et le sauvegarder
        QString initialHash = generateHashFromFile(dbPath);
        if (!initialHash.isEmpty()) {
            if (!saveHashToFile(initialHash)) {
                qDebug() << QObject::tr("Erreur : Échec de la sauvegarde du hash.");
                return false;
            }
        } else {
            qDebug() << QObject::tr("Erreur : Échec de la génération du hash.");
            return false;
        }

        // 3. Modifier les droits en écriture sur la base de données copiée
        QFile::setPermissions(dbPath, QFileDevice::WriteOwner | QFileDevice::ReadOwner);

        // 4. Ouvrir la base de données et insérer les données par défaut
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            qDebug() << QObject::tr("Erreur : Impossible d'ouvrir la base de données SQLite après copie.");
            return false;
        }

        // Insertion des données par défaut
        if (!insertDefaultData(db)) {
            qDebug() << QObject::tr("Erreur : Impossible d'insérer les données par défaut.");
            db.close();
            return false;
        }

        db.close(); // Fermer la base de données après insertion
        qDebug() << QObject::tr("Données par défaut insérées avec succès.");

    } else {
        // Cas où la base de données existe déjà
        // 1. Générer le hash de la base de référence dans les ressources
        QString referenceHash = generateHashFromFile(":/database/ICyamBank.db");

        // 2. Charger le hash sauvegardé
        QString savedHash = loadHashFromFile();

        // 3. Comparer les deux hash
        if (referenceHash != savedHash) {
            // Si les hash sont différents, informer de la nécessité d'une mise à jour
            QMessageBox::information(nullptr, QObject::tr("Mise à jour requise"), QObject::tr("La base de données doit être mise à jour."));
            qDebug() << QObject::tr("Attention : La base de données nécessite une mise à jour.");
        } else {
            qDebug() << QObject::tr("La base de données est à jour.");
        }
    }

    return true;
}

// Fonction pour insérer les données par défaut dans la langue de l'utilisateur
bool databaseManager::insertDefaultData(QSqlDatabase &db) {
    QSqlQuery query(db);

    // Traduction des textes français par la langue active
    QString balanceGroup = QObject::tr("Comptes de Bilan");
    QString profitGroup = QObject::tr("Comptes de Bénéfice et de Perte");

    // Traduction des types de comptes pour le groupe de Bilan
    QString banksType = QObject::tr("Banques");
    QString walletsType = QObject::tr("Portefeuilles");
    QString assetsType = QObject::tr("Biens");
    QString debtsType = QObject::tr("Dettes");
    QString capitalType = QObject::tr("Capital");

    // Traduction des types de comptes pour le groupe de Bénéfice et de Perte
    QString incomeType = QObject::tr("Revenus");
    QString expensesType = QObject::tr("Dépenses");

    // Insertion des groupes de comptes
    if (!query.exec(QString("INSERT INTO account_groups (name_group) VALUES ('%1')").arg(balanceGroup))) {
        qDebug() << "Erreur d'insertion pour le groupe de Bilan:" << query.lastError().text();
        return false;
    }
    if (!query.exec(QString("INSERT INTO account_groups (name_group) VALUES ('%1')").arg(profitGroup))) {
        qDebug() << "Erreur d'insertion pour le groupe de Bénéfice et de Perte:" << query.lastError().text();
        return false;
    }

    // Récupérer l'id du groupe de Bilan pour l'insertion des types
    int balanceGroupId = query.lastInsertId().toInt();

    // Insertion des types de comptes pour le groupe de Bilan
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(balanceGroupId).arg(banksType))) {
        qDebug() << "Erreur d'insertion pour le type Banques:" << query.lastError().text();
        return false;
    }
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(balanceGroupId).arg(walletsType))) {
        qDebug() << "Erreur d'insertion pour le type Portefeuilles:" << query.lastError().text();
        return false;
    }
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(balanceGroupId).arg(assetsType))) {
        qDebug() << "Erreur d'insertion pour le type Biens:" << query.lastError().text();
        return false;
    }
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(balanceGroupId).arg(debtsType))) {
        qDebug() << "Erreur d'insertion pour le type Dettes:" << query.lastError().text();
        return false;
    }
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(balanceGroupId).arg(capitalType))) {
        qDebug() << "Erreur d'insertion pour le type Capital:" << query.lastError().text();
        return false;
    }

    // Récupérer l'id du groupe de Bénéfice et de Perte pour l'insertion des types
    int profitGroupId = query.lastInsertId().toInt();

    // Insertion des types de comptes pour le groupe de Bénéfice et de Perte
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(profitGroupId).arg(incomeType))) {
        qDebug() << "Erreur d'insertion pour le type Revenus:" << query.lastError().text();
        return false;
    }
    if (!query.exec(QString("INSERT INTO account_types (id_group, name_type) VALUES (%1, '%2')").arg(profitGroupId).arg(expensesType))) {
        qDebug() << "Erreur d'insertion pour le type Dépenses:" << query.lastError().text();
        return false;
    }

    qDebug() << "Données par défaut insérées avec succès.";
    return true;
}
