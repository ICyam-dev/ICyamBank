#ifndef OBJICYAMAPP_H
#define OBJICYAMAPP_H

#include <QString>
#include <QDateTime>

class objICyamApp
{
public:
    // Gestion de l'ID du dossier sélectionné
    // Managing selected folder ID
    static int getSelectedFolderId();             // Obtenir l'ID du dossier sélectionné / Get selected folder ID
    static void setSelectedFolderId(int folderId); // Définir l'ID du dossier sélectionné / Set selected folder ID

    // Chemins et fichiers
    // Paths and files
    static QString getAppPath();                  // Obtenir le chemin du répertoire de l'application / Get application directory path
    static QString getDatabasePath();             // Obtenir le chemin de la base de données / Get database path
    static QString getLogsPath();                 // Obtenir le chemin du répertoire des journaux / Get logs directory path
    static QString getConfigFilePath();           // Obtenir le chemin du fichier de configuration / Get config file path

    // Initialisation de la base de données
    // Database initialization
    static int initDatabase(const QString &databaseFileName); // Initialiser la base de données avec un fichier donné / Initialize the database with a given file

    // Intégrité de la base de données
    // Database integrity
    static bool verifyDatabaseIntegrity(const QString &databaseFileName); // Vérifier l'intégrité de la base de données / Verify database integrity

    // Gestion du hash de la base de données
    // Database hash management
    static bool saveHashToFile(const QString &hash);        // Sauvegarder un hash dans un fichier / Save a hash to a file
    static QString generateHash(const QString &input);      // Générer un hash à partir d'une chaîne de caractères / Generate a hash from a string

    // Préférences utilisateur
    // User preferences
    static QString getUserLanguage();                        // Obtenir la langue de l'utilisateur / Get user language
    static void setUserLanguage(const QString &language);    // Définir la langue de l'utilisateur / Set user language
    static QString getTheme();                               // Obtenir le thème de l'application / Get application theme
    static void setTheme(const QString &theme);              // Définir le thème de l'application / Set application theme

    // Utilitaires de sécurité
    // Security utilities
    static bool verifyPassword(const QString &input, const QString &storedHash); // Vérifier le mot de passe en comparant un hash / Verify password by comparing a hash

    // Autres utilitaires
    // Other utilities
    static QDateTime getCurrentDateTime();                   // Obtenir la date et l'heure actuelles / Get current date and time

    // Méthodes de configuration
    // Configuration methods
    static bool setupDatabase();                             // Configurer la base de données / Set up the database
    static void resetApplicationData();                      // Réinitialiser les données de l'application / Reset application data

private:
    static int selectedFolderId;  // ID du dossier sélectionné, accessible uniquement via les méthodes publiques
        // Selected folder ID, accessible only through public methods

    static int m_folderId;  // Déclaré comme membre statique pour persistance

    // **Générer un hash à partir d'un fichier / Generate a hash from a file**
    static QString generateHashFromFile(const QString &filePath); // Générer un hash à partir du contenu d'un fichier / Generate a hash from file content
};

#endif // OBJICYAMAPP_H
