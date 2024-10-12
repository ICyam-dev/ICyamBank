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
    qDebug() << "Chemin du fichier hash:" << hashFilePath;

    return hashFilePath;
}

QString databaseManager::generateHashFromFile(const QString &filePath) {
    // Générer un hash SHA256 à partir du contenu d'un fichier
    // Generate a SHA256 hash from the contents of a file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QObject::tr("Erreur : Impossible d'ouvrir le fichier pour générer le hash.") << filePath;
        // Affiche également le chemin du fichier
        // Also displays the file path
        return QString();
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);  // Utiliser l'algorithme SHA256 // Using SHA256 algorithm
    if (hash.addData(&file)) {
        // Retourner le hash sous forme de chaîne hexadécimale
        // Return the hash as a hexadecimal string
        return QString(hash.result().toHex());
    }

    return QString();
}

bool databaseManager::saveHashToFile(const QString &hash) {
    // Sauvegarder le hash dans un fichier
    // Save the hash to a file
    QString hashFilePath = getHashFilePath();

    QFile file(hashFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de sauvegarder le fichier hash.") << hashFilePath;
        // Affiche également le chemin du fichier
        // Also displays the file path
        return false;
    }

    QTextStream out(&file);
    out << hash;

    // Ajout d'un message pour confirmer la sauvegarde
    // Added a message to confirm the save
    qDebug() << QObject::tr("Hash sauvegardé avec succès.") << hashFilePath;
    return true;
}

QString databaseManager::loadHashFromFile() {
    // Charger le hash sauvegardé à partir du fichier
    // Load the saved hash from the file
    QString hashFilePath = getHashFilePath();

    QFile file(hashFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de lire le fichier hash.") << hashFilePath;
        // Affiche également le chemin du fichier
        // Also displays the file path
        return QString();
    }

    QTextStream in(&file);
    QString hash = in.readAll().trimmed();

    // Ajout d'un message pour confirmer le chargement
    // Added a message to confirm the loading
    qDebug() << QObject::tr("Hash chargé avec succès.") << hashFilePath;
    return hash;
}

bool databaseManager::setupDatabase() {
    QString dbPath = getDatabasePath();

    // Créer le répertoire s'il n'existe pas
    // Create the directory if it doesn't exist
    QDir dir;
    if (!dir.exists(QFileInfo(dbPath).path())) {
        if (!dir.mkpath(QFileInfo(dbPath).path())) {
            qDebug() << QObject::tr("Erreur : Impossible de créer le répertoire ICyamBank.");
            return false;
        }
    }

    // Si la base de données n'existe pas
    // If the database does not exist
    if (!QFile::exists(dbPath)) {
        // 1. Copier la base de données depuis les ressources
        // 1. Copy the database from the resources
        if (!QFile::copy(":/database/ICyamBank.db", dbPath)) {
            qDebug() << QObject::tr("Erreur : Échec de la copie de la base de données vierge.");
            return false;
        }
        qDebug() << QObject::tr("Base de données vierge copiée avec succès.");

        // 2. Générer le hash de la base copiée et le sauvegarder
        // 2. Generate the hash of the copied database and save it
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
        // 3. Modify write permissions on the copied database
        QFile::setPermissions(dbPath, QFileDevice::WriteOwner | QFileDevice::ReadOwner);

    } else {
        // Cas où la base de données existe déjà
        // Case when the database already exists
        QString referenceHash = generateHashFromFile(":/database/ICyamBank.db");
        QString savedHash = loadHashFromFile();

        // Si les hash sont différents, informer de la nécessité d'une mise à jour
        // If the hashes differ, inform of the need for an update
        if (referenceHash != savedHash) {
            QMessageBox::information(nullptr, QObject::tr("Mise à jour requise"), QObject::tr("La base de données doit être mise à jour."));
            qDebug() << QObject::tr("Attention : La base de données nécessite une mise à jour.");
        } else {
            qDebug() << QObject::tr("La base de données est à jour.");
        }
    }

    // Vérifier et ouvrir la base de données pour des usages ultérieurs
    // Verify and open the database for further use
    QSqlDatabase db = QSqlDatabase::database("ICyamBankConnection");
    if (!db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE", "ICyamBankConnection");
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            qDebug() << QObject::tr("Erreur : Impossible d'ouvrir la base de données SQLite.");
            return false;
        }
    }

    return true;
}
