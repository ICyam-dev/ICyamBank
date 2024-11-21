#include "header/databaseManager.h"
#include "header/objICyamApp.h"  // Inclusion de objICyamApp pour utiliser les méthodes centralisées / Including objICyamApp to use centralized methods
#include <QFile>           // Pour la gestion de fichiers / For file management
#include <QSqlDatabase>    // Pour les connexions à la base de données / For database connections
#include <QSqlQuery>       // Pour exécuter les requêtes SQL / For executing SQL queries
#include <QSqlError>       // Pour capturer les erreurs SQL / For capturing SQL errors
#include <QDebug>          // Pour les messages de débogage / For debugging messages

// **Désactivation et suppression logique / Soft Delete and Deactivation**

// Désactive une banque spécifique en définissant son champ `is_active` à 0
// Deactivates a specific bank by setting its `is_active` field to 0
bool databaseManager::deactivateBank(int bankId) {
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("UPDATE bank SET is_active = 0 WHERE id_bank = :id");
    query.bindValue(":id", bankId);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la désactivation de la banque:" << query.lastError().text();
        return false;
    }
    return true;
}

// Désactive tous les comptes associés à une banque spécifique
// Deactivates all accounts associated with a specific bank
bool databaseManager::deactivateAccountsForBank(int bankId) {
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("UPDATE account SET is_active = 0 WHERE id_bank = :id");
    query.bindValue(":id", bankId);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la désactivation des comptes pour la banque:" << query.lastError().text();
        return false;
    }
    return true;
}

// **Insertion des données par défaut / Inserting Default Data**

// Insère des types de comptes par défaut si la table `type_account` existe
// Inserts default account types if the `type_account` table exists
void databaseManager::insertDefaultAccountTypes() {
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
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

// Insère un utilisateur par défaut dans la base de données si la table `user` existe
// Inserts a default user into the database if the `user` table exists
void databaseManager::insertDefaultUser() {
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
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

// **Récupération de la dernière insertion / Retrieving the Last Insertion**

// Récupère l'ID de la dernière banque insérée ou -1 si une erreur survient
// Retrieves the ID of the last inserted bank, or -1 if an error occurs
int databaseManager::getLastInsertedBankId() {
    QSqlQuery query;
    query.exec("SELECT last_insert_rowid() FROM bank");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

// Récupère l'ID du dernier groupe inséré ou -1 en cas d'échec
// Retrieves the ID of the last inserted group, or -1 on failure
int databaseManager::getLastInsertedGroupId() {
    QSqlQuery query;
    query.exec("SELECT last_insert_rowid() FROM group_account");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}
