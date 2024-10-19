#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class databaseManager {
public:
    // Méthode pour configurer la base de données // Method to set up the database
    static bool setupDatabase();

    // Méthode pour récupérer le chemin de la base de données // Method to get the path of the database
    static QString getDatabasePath();

    // Méthode pour insérer les données par défaut // Method to insert default data
    static bool insertDefaultData(QSqlDatabase &db);

    // Méthode pour désactiver une banque (soft delete) // Method to deactivate a bank (soft delete)
    static bool deactivateBank(int bankId);

    // Méthode pour désactiver tous les comptes associés à une banque désactivée (soft delete) // Method to deactivate all accounts associated with a deactivated bank (soft delete)
    static bool deactivateAccountsForBank(int bankId);

private:
    // Méthode pour obtenir le chemin du fichier de hash // Method to get the hash file path
    static QString getHashFilePath();

    // Méthode pour générer un hash à partir d'un fichier // Method to generate a hash from a file
    static QString generateHashFromFile(const QString &filePath);

    // Méthode pour sauvegarder un hash dans un fichier // Method to save a hash to a file
    static bool saveHashToFile(const QString &hash);

    // Méthode pour charger un hash à partir d'un fichier // Method to load a hash from a file
    static QString loadHashFromFile();
};

#endif // DATABASEMANAGER_H
