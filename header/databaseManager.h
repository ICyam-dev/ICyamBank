#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class databaseManager {
public:
    // Configuration de la base de données / Database configuration
    static bool setupDatabase();  // Configurer la base de données / Set up the database
    static QString getDatabasePath();  // Obtenir le chemin de la base de données / Retrieve the database path

    // Gestion des types de comptes et des utilisateurs par défaut / Management of default account types and users
    static void insertDefaultAccountTypes();  // Insérer les types de comptes par défaut / Insert default account types
    void insertDefaultUser();  // Insérer un utilisateur par défaut / Insert a default user
    static bool insertDefaultData(QSqlDatabase &db);  // Insérer les données par défaut dans la base / Insert default data into the database

    // Gestion des banques et des comptes / Management of banks and accounts
    static bool deactivateBank(int bankId);  // Désactiver une banque (soft delete) / Deactivate a bank (soft delete)
    static bool deactivateAccountsForBank(int bankId);  // Désactiver tous les comptes associés à une banque / Deactivate all accounts associated with a bank

    // Gestion du dossier en cours / Current folder management
    static int getCurrentFolderId();  // Obtenir l'ID du dossier en cours / Get current folder ID
    static void setCurrentFolderId(int folderId);  // Définir l'ID du dossier en cours / Set current folder ID

    // Récupération des derniers IDs insérés / Retrieve last inserted IDs
    static int getLastInsertedBankId();  // Récupérer l'ID de la dernière banque insérée / Retrieve the last inserted bank ID
    static int getLastInsertedGroupId();  // Récupérer l'ID du dernier groupe inséré / Retrieve the last inserted group ID

private:
    // Gestion des fichiers de hashage / Hash file management
    static QString getHashFilePath();  // Obtenir le chemin du fichier de hash / Get hash file path
    static QString generateHashFromFile(const QString &filePath);  // Générer un hash à partir d'un fichier / Generate a hash from a file
    static bool saveHashToFile(const QString &hash);  // Sauvegarder un hash dans un fichier / Save a hash to a file
    static QString loadHashFromFile();  // Charger un hash à partir d'un fichier / Load a hash from a file

    // Variable statique pour stocker l'index du dossier / Static variable to store folder ID
    static int currentFolderId;
};

#endif // DATABASEMANAGER_H
