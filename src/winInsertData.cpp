#include "header/winInsertData.h"
#include "header/objICyamApp.h"
#include "ui_winInsertData.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// Constructeur de la classe winInsertData / Constructor for winInsertData class
winInsertData::winInsertData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winInsertData)
{
    ui->setupUi(this);
    configureWindow();  // Configurer la fenêtre au démarrage / Configure window on startup

    // Connexions des boutons aux slots / Connect buttons to slots
    connect(ui->BtnNo, &QPushButton::clicked, this, &winInsertData::reject);
    connect(ui->BtnYes, &QPushButton::clicked, this, &winInsertData::insertExampleDataAndClose);
}

// Configurer les paramètres de la fenêtre / Configure window settings
void winInsertData::configureWindow()
{
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(this->size());  // Fixer la taille de la fenêtre / Set fixed window size
}

// Insérer les données d'exemple et fermer les fenêtres / Insert example data and close windows
void winInsertData::insertExampleDataAndClose()
{
    int folderId = objICyamApp::getSelectedFolderId();
    qDebug() << "Début de l'insertion des données d'exemple pour le dossier ID:" << folderId;

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));

    // **Étape 1 : Insérer les banques** / **Step 1: Insert banks**
    int id_bank_emerald = insertBank(query, folderId, QObject::tr("Banque Émeraude"));
    int id_bank_sapphire = insertBank(query, folderId, QObject::tr("Banque Saphir"));

    // Vérifier l'insertion des banques / Check bank insertion
    if (id_bank_emerald == -1 || id_bank_sapphire == -1) {
        QMessageBox::warning(this, tr("Erreur"), tr("Erreur lors de l'insertion des banques. Opération annulée."));
        return;
    }

    int defaultCurrencyId = 1;  // ID de la devise par défaut / Default currency ID

    // **Étape 2 : Insérer les comptes pour chaque banque** / **Step 2: Insert accounts for each bank**
    QList<int> emeraldAccounts, sapphireAccounts;
    emeraldAccounts << insertAccount(query, folderId, id_bank_emerald, QObject::tr("Compte Émeraude Personnel"), 1, defaultCurrencyId, 1500.0);
    emeraldAccounts << insertAccount(query, folderId, id_bank_emerald, QObject::tr("Compte Émeraude Épargne"), 2, defaultCurrencyId, 5000.0);
    emeraldAccounts << insertAccount(query, folderId, id_bank_emerald, QObject::tr("Compte Émeraude Business"), 3, defaultCurrencyId, 12000.0);

    sapphireAccounts << insertAccount(query, folderId, id_bank_sapphire, QObject::tr("Compte Saphir Personnel"), 1, defaultCurrencyId, 2000.0);
    sapphireAccounts << insertAccount(query, folderId, id_bank_sapphire, QObject::tr("Compte Saphir Épargne"), 2, defaultCurrencyId, 8000.0);

    // **Étape 3 : Insérer les groupes** / **Step 3: Insert groups**
    int id_group_economy = insertGroup(query, folderId, QObject::tr("Groupe Économie"));
    int id_group_business = insertGroup(query, folderId, QObject::tr("Groupe Business"));
    int id_group_personal = insertGroup(query, folderId, QObject::tr("Groupe Personnel"));

    // Vérifier l'insertion des groupes / Check group insertion
    if (id_group_economy == -1 || id_group_business == -1 || id_group_personal == -1) {
        QMessageBox::warning(this, tr("Erreur"), tr("Erreur lors de l'insertion des groupes. Opération annulée."));
        return;
    }

    // **Étape 4 : Associer les comptes aux groupes** / **Step 4: Associate accounts with groups**
    assignAccountsToGroup(query, id_group_economy, {emeraldAccounts[1], sapphireAccounts[1]});
    assignAccountsToGroup(query, id_group_business, {emeraldAccounts[2], sapphireAccounts[0]});

    // Fermer winInsertData et winUser (la fenêtre parente) après l'insertion / Close winInsertData and parent winUser after insertion
    QDialog *parentDialog = qobject_cast<QDialog*>(parent());
    if (parentDialog) {
        parentDialog->accept();  // Fermer winUser / Close winUser
    }
    this->accept();  // Fermer winInsertData / Close winInsertData
}

// Insérer une banque dans la base de données / Insert a bank into the database
int winInsertData::insertBank(QSqlQuery &query, int id_folder, const QString &bankName) {
    query.prepare("INSERT INTO bank (id_folder, bank_name) VALUES (:id_folder, :bank_name)");
    query.bindValue(":id_folder", id_folder);
    query.bindValue(":bank_name", bankName);

    if (!query.exec()) {
        qDebug() << QObject::tr("Erreur lors de l'insertion de la banque") << bankName << ":" << query.lastError().text();
        return -1;  // Retourner -1 en cas d'erreur / Return -1 if an error occurs
    }
    return query.lastInsertId().toInt();  // Retourner l'ID de la banque insérée / Return the inserted bank ID
}

// Insérer un compte dans la base de données / Insert an account into the database
int winInsertData::insertAccount(QSqlQuery &query, int id_folder, int id_bank, const QString &accountName, int id_type, int id_devise, double balance) {
    query.prepare("INSERT INTO account (id_folder, id_bank, account_name, id_type, id_devise, balance) "
                  "VALUES (:id_folder, :id_bank, :account_name, :id_type, :id_devise, :balance)");
    query.bindValue(":id_folder", id_folder);
    query.bindValue(":id_bank", id_bank);
    query.bindValue(":account_name", accountName);
    query.bindValue(":id_type", id_type);
    query.bindValue(":id_devise", id_devise);
    query.bindValue(":balance", balance);

    if (!query.exec()) {
        qDebug() << QObject::tr("Erreur lors de l'insertion du compte") << accountName << ":" << query.lastError().text();
        return -1;  // Retourner -1 en cas d'échec / Return -1 on failure
    }
    return query.lastInsertId().toInt();  // Retourner l'ID du compte inséré / Return inserted account ID
}

// Insérer un groupe dans la base de données / Insert a group into the database
int winInsertData::insertGroup(QSqlQuery &query, int id_folder, const QString &groupName) {
    query.prepare("INSERT INTO group_account (id_folder, name_group) VALUES (:id_folder, :name_group)");
    query.bindValue(":id_folder", id_folder);
    query.bindValue(":name_group", groupName);

    if (!query.exec()) {
        qDebug() << QObject::tr("Erreur lors de l'insertion du groupe") << groupName << ":" << query.lastError().text();
        return -1;  // Retourner -1 en cas d'échec / Return -1 on failure
    }
    return query.lastInsertId().toInt();  // Retourner l'ID du groupe inséré / Return inserted group ID
}

// Associer des comptes à un groupe spécifique / Associate accounts with a specific group
void winInsertData::assignAccountsToGroup(QSqlQuery &query, int id_group, const QList<int> &accountIds) {
    for (int accountId : accountIds) {
        query.prepare("UPDATE account SET id_group = :id_group WHERE id_account = :id_account");
        query.bindValue(":id_group", id_group);
        query.bindValue(":id_account", accountId);

        if (!query.exec()) {
            qDebug() << QObject::tr("Erreur lors de l'association du compte ID") << accountId << QObject::tr("au groupe ID") << id_group << ":" << query.lastError().text();
        }
    }
}

// Afficher un message contenant l'ID du dossier actuel / Display a message with the current folder ID
void winInsertData::showFolderIdMessage() {
    int folderId = objICyamApp::getSelectedFolderId();
    QMessageBox::information(this, tr("ID du dossier"), tr("L'ID du dossier actuel est : %1").arg(folderId));
}

// Destructeur de la classe / Destructor of the class
winInsertData::~winInsertData() {
    delete ui;
}
