#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class databaseManager {
public:
    static bool setupDatabase();  // Configurer la base de données // Set up the database
    static QString getDatabasePath();  // Récupérer le chemin de la base de données // Get the path of the database
    static bool insertDefaultData(QSqlDatabase &db);  // Insérer les données par défaut // Insert default data

private:
    static QString getHashFilePath();  // Récupérer le chemin du fichier de hash // Get the hash file path
    static QString generateHashFromFile(const QString &filePath);  // Générer un hash à partir d'un fichier // Generate a hash from a file
    static bool saveHashToFile(const QString &hash);  // Sauvegarder un hash dans un fichier // Save a hash to a file
    static QString loadHashFromFile();  // Charger un hash à partir d'un fichier // Load a hash from a file
};

#endif // DATABASEMANAGER_H
