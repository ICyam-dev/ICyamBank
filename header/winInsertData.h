#ifndef WININSERTDATA_H
#define WININSERTDATA_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class winInsertData;
}

class winInsertData : public QDialog
{
    Q_OBJECT

public:
    explicit winInsertData(QWidget *parent = nullptr);
    ~winInsertData();

public slots:
    // Afficher un message contenant l'ID du dossier actuel
    // Show a message containing the current folder ID
    void showFolderIdMessage();

private:
    Ui::winInsertData *ui;

    // Insérer une banque dans la base de données pour un dossier donné
    // Insert a bank into the database for a given folder
    int insertBank(QSqlQuery &query, int id_folder, const QString &bankName);

    // Insérer un compte dans la base de données pour une banque et un dossier donnés
    // Insert an account into the database for a given bank and folder
    int insertAccount(QSqlQuery &query, int id_folder, int id_bank, const QString &accountName, int id_type, int id_devise, double balance);

    // Insérer un groupe dans la base de données pour un dossier donné
    // Insert a group into the database for a given folder
    int insertGroup(QSqlQuery &query, int id_folder, const QString &groupName);

    // Associer une liste de comptes à un groupe spécifique
    // Assign a list of accounts to a specific group
    void assignAccountsToGroup(QSqlQuery &query, int id_group, const QList<int> &accountIds);

    // Configurer les propriétés de la fenêtre / Set up window properties
    void configureWindow();

    // Insérer des données d'exemple et fermer la fenêtre / Insert sample data and close the window
    void insertExampleDataAndClose();
};

#endif // WININSERTDATA_H
