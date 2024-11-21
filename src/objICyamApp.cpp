#include "header/objICyamApp.h"
#include <QFile>             // Pour la gestion des fichiers / For file handling
#include <QTextStream>       // Pour lire et écrire du texte dans des fichiers / For reading and writing text in files
#include <QDir>              // Pour la gestion des répertoires / For directory management
#include <QStandardPaths>    // Pour accéder aux chemins standards du système / For accessing system standard paths
#include <QDebug>            // Pour les messages de débogage / For debug messages
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QCryptographicHash>

// Initialisation de selectedFolderId à -1 pour indiquer qu'aucun dossier n'est sélectionné
// Initialize selectedFolderId to -1 to indicate that no folder is selected
int objICyamApp::selectedFolderId = -1;
int objICyamApp::m_folderId = -1;

// Récupérer l'ID du dossier sélectionné / Get the selected folder ID
int objICyamApp::getSelectedFolderId() {
    return m_folderId;
}

// Définir l'ID du dossier sélectionné / Set the selected folder ID
void objICyamApp::setSelectedFolderId(int folderId) {
    m_folderId = folderId;
}

// **Chemins et fichiers / Paths and files**
// Obtenir le chemin du répertoire de données de l'application, et le créer s'il n'existe pas.
// Get the application data directory path, and create it if it doesn't exist.
QString objICyamApp::getAppPath() {
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);

    if (!dir.exists()) {
        dir.mkpath(appDataPath);  // Créer le répertoire s'il n'existe pas déjà / Create the directory if it doesn't already exist
    }

    return appDataPath;
}

// Obtenir et créer le chemin du répertoire de la base de données dans le dossier Documents
// Get and create the database directory path in the Documents folder
QString objICyamApp::getDatabasePath() {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString dbDirectory = documentsPath + "/ICyamBank";

    QDir dir(dbDirectory);
    if (!dir.exists()) {
        dir.mkpath(dbDirectory);  // Créer le répertoire "ICyamBank" s'il n'existe pas / Create the "ICyamBank" directory if it doesn't exist
    }

    return dbDirectory;  // Retourne le chemin complet de la base de données / Returns the full database path
}

// **Initialiser la base de données / Initialize the database**
// Initialise la base de données, vérifie et crée les répertoires, et charge les données initiales si nécessaire
// Initializes the database, checks and creates directories, and loads initial data if needed
int objICyamApp::initDatabase(const QString &databaseFileName) {
    QString dbPath = getDatabasePath() + "/" + databaseFileName;
    qDebug() << "Chemin de la base de données déterminé :" << dbPath;  // Afficher le chemin / Display the path

    QDir dir;
    QString dbDirectoryPath = QFileInfo(dbPath).path();
    if (!dir.exists(dbDirectoryPath) && !dir.mkpath(dbDirectoryPath)) {
        qDebug() << QObject::tr("Erreur : Impossible de créer le répertoire de la base de données.");
        return -1;  // Échec de la création du répertoire / Directory creation failed
    }

    QString documentsDirectory = dbDirectoryPath + "/_docs";
    if (!dir.exists(documentsDirectory) && !dir.mkpath(documentsDirectory)) {
        qDebug() << QObject::tr("Erreur : Impossible de créer le répertoire 'documents'.");
        return -1;  // Échec de la création du répertoire de documents / Documents directory creation failed
    }

    bool databaseJustCreated = false;
    if (!QFile::exists(dbPath)) {
        QString tempDbPath = dbPath + "_temp";
        if (!QFile::copy(":/database/_dataBase.db", tempDbPath) || !QFile::rename(tempDbPath, dbPath)) {
            qDebug() << QObject::tr("Erreur : Impossible de copier ou renommer la base de données.");
            QFile::remove(tempDbPath);  // Supprimer en cas d'erreur / Remove if an error occurs
            return -1;  // Échec de copie ou de renommage de la base de données / Database copy or rename failed
        }

        databaseJustCreated = true;
        QString initialHash = generateHashFromFile(dbPath);
        if (!initialHash.isEmpty() && !saveHashToFile(initialHash)) {
            return -1;  // Échec de la sauvegarde du hash / Hash save failed
        }

        QFile::setPermissions(dbPath, QFileDevice::WriteOwner | QFileDevice::ReadOwner);  // Définir les permissions / Set permissions
    }

    if (!databaseJustCreated && !verifyDatabaseIntegrity(databaseFileName)) {
        QMessageBox::critical(nullptr, QObject::tr("Intégrité de la base de données"),
                              QObject::tr("La base de données n'est pas à jour. L'application va s'arrêter."));
        return -1;  // Base de données non conforme / Database integrity check failed
    }

    QSqlDatabase db = QSqlDatabase::database("ICyamConnection");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE", "ICyamConnection");
        db.setDatabaseName(dbPath);
    }

    if (!db.open()) {
        qDebug() << QObject::tr("Erreur : Impossible d'ouvrir la base de données SQLite.") << db.lastError().text();
        return -1;  // Échec de l'ouverture de la base de données / Database open failed
    }

    return databaseJustCreated ? 1 : 0;  // Retourne 1 si la base est nouvelle, sinon 0 / Returns 1 if the database is new, otherwise 0
}

// **Sauvegarder un hash dans un fichier situé au même endroit que la base de données utilisateur / Save hash to a file in the same location as the user database**
// Sauvegarde un hash dans un fichier pour vérifier l'intégrité des données ultérieurement
// Saves a hash to a file for verifying data integrity later
bool objICyamApp::saveHashToFile(const QString &hash) {
    QString hashFilePath = getDatabasePath() + "/db_hash";
    QFile file(hashFilePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QObject::tr("Erreur : Impossible de sauvegarder le fichier hash.") << hashFilePath;
        return false;
    }

    QTextStream out(&file);
    out << hash;  // Écrire le hash dans le fichier / Write hash to file
    return true;
}

// **Vérifier l'intégrité de la base de données en comparant le hash / Verify database integrity by comparing hash**
// Vérifie l'intégrité de la base en comparant un hash enregistré et le hash de référence
// Checks database integrity by comparing a saved hash and a reference hash
bool objICyamApp::verifyDatabaseIntegrity(const QString &databaseFileName) {
    QString storedHashPath = getDatabasePath() + "/db_hash";
    QString refDbPath = ":/database/_dataBase.db";

    QString storedHash;
    QFile file(storedHashPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        storedHash = in.readLine().trimmed();
        file.close();
    } else {
        qDebug() << QObject::tr("Erreur : Impossible de lire le fichier de hash stocké.");
        return false;
    }

    QString refDbHash = generateHashFromFile(refDbPath);
    if (refDbHash.isEmpty()) {
        qDebug() << QObject::tr("Erreur : Impossible de générer le hash de la base de données de référence.");
        return false;
    }

    return (storedHash == refDbHash);  // Comparaison du hash stocké avec celui de référence / Compare stored hash with reference hash
}

// **Obtenir le chemin des journaux / Get logs path**
// Retourne le chemin du répertoire de journaux, en le créant s'il n'existe pas
// Returns the logs directory path, creating it if it doesn't exist
QString objICyamApp::getLogsPath() {
    QString logsPath = getAppPath() + "/logs";
    QDir dir(logsPath);

    if (!dir.exists()) {
        dir.mkpath(logsPath);  // Créer le répertoire des journaux s'il n'existe pas / Create the logs directory if it doesn't exist
    }

    return logsPath;
}

// **Obtenir le chemin du fichier de configuration / Get config file path**
// Retourne le chemin du fichier de configuration
// Returns the config file path
QString objICyamApp::getConfigFilePath() {
    return getDatabasePath() + "/config.ini";
}

// **Générer un hash à partir du fichier spécifié / Generate a hash from the specified file**
// Génère un hash SHA-256 pour vérifier l'intégrité d'un fichier
// Generates a SHA-256 hash to verify file integrity
QString objICyamApp::generateHashFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QObject::tr("Erreur : Impossible d'ouvrir le fichier pour générer le hash.") << filePath;
        return QString();
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);  // Utiliser SHA-256 pour le hash / Use SHA-256 for hashing
    if (hash.addData(&file)) {
        return hash.result().toHex();  // Retourne le hash en hexadécimal / Return the hash in hexadecimal format
    } else {
        qDebug() << QObject::tr("Erreur : Impossible de lire les données pour le hashage.") << filePath;
        return QString();
    }
}

// **Préférences utilisateur / User preferences**

// Retourne la langue de l'utilisateur par défaut / Returns default user language
QString objICyamApp::getUserLanguage() {
    return QString();
}

// Définir la langue de l'utilisateur / Set user language
void objICyamApp::setUserLanguage(const QString &language) {
    Q_UNUSED(language);
}

// Retourne le thème actuel par défaut / Returns the default theme
QString objICyamApp::getTheme() {
    return QString();
}

// Définir le thème de l'application / Set application theme
void objICyamApp::setTheme(const QString &theme) {
    Q_UNUSED(theme);
}

// **Utilitaires de sécurité / Security utilities**

// Génère un hash basé sur l'entrée (valeur par défaut pour l'instant)
// Generates a hash based on input (default value for now)
QString objICyamApp::generateHash(const QString &input) {
    Q_UNUSED(input);
    return QString();
}

// Vérifie si le mot de passe correspond au hash (valeur par défaut pour l'instant)
// Checks if the password matches the stored hash (default value for now)
bool objICyamApp::verifyPassword(const QString &input, const QString &storedHash) {
    Q_UNUSED(input);
    Q_UNUSED(storedHash);
    return false;
}

// **Autres utilitaires / Other utilities**

// Retourne la date et l'heure actuelles par défaut
// Returns the current date and time by default
QDateTime objICyamApp::getCurrentDateTime() {
    return QDateTime();
}

// **Méthodes de configuration / Configuration methods**

// Configure la base de données (valeur par défaut pour l'instant)
// Sets up the database (default value for now)
bool objICyamApp::setupDatabase() {
    return false;
}

// Réinitialise les données de l'application
// Resets application data
void objICyamApp::resetApplicationData() {
}
