#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class databaseManager {
public:
    // **Configuration de la base de données / Database configuration**
    static bool setupDatabase();                          // Configurer la base de données / Set up the database

    // **Gestion des types de comptes et des utilisateurs par défaut / Management of default account types and users**
    static void insertDefaultAccountTypes();              // Insérer les types de comptes par défaut / Insert default account types
    static void insertDefaultUser();                             // Insérer un utilisateur par défaut / Insert a default user
    static bool insertDefaultData(QSqlDatabase &db);      // Insérer les données par défaut dans la base / Insert default data into the database

    // **Gestion des banques et des comptes / Management of banks and accounts**
    static bool deactivateBank(int bankId);               // Désactiver une banque (soft delete) / Deactivate a bank (soft delete)
    static bool deactivateAccountsForBank(int bankId);    // Désactiver tous les comptes associés à une banque / Deactivate all accounts associated with a bank

    // **Récupération des derniers IDs insérés / Retrieve last inserted IDs**
    static int getLastInsertedBankId();                   // Récupérer l'ID de la dernière banque insérée / Retrieve the last inserted bank ID
    static int getLastInsertedGroupId();                  // Récupérer l'ID du dernier groupe inséré / Retrieve the last inserted group ID

private:
    // **Gestion des fichiers de hashage / Hash file management**
    static QString getHashFilePath();                     // Obtenir le chemin du fichier de hash / Get hash file path
    static QString generateHashFromFile(const QString &filePath);  // Générer un hash à partir d'un fichier / Generate a hash from a file
    static bool saveHashToFile(const QString &hash);      // Sauvegarder un hash dans un fichier / Save a hash to a file
    static QString loadHashFromFile();                    // Charger un hash à partir d'un fichier / Load a hash from a file
};

#endif // DATABASEMANAGER_H
