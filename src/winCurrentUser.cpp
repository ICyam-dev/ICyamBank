#include "header/winCurrentUser.h"
#include "header/objICyamApp.h"
#include "ui_winCurrentUser.h"
#include "header/databaseManager.h"  // Inclusion pour gérer les requêtes SQL / Include to manage SQL queries
#include <QSqlQuery>                 // Pour exécuter des requêtes SQL / To execute SQL queries
#include <QSqlError>                 // Pour gérer les erreurs SQL / To handle SQL errors
#include <QMessageBox>               // Pour afficher des messages d'erreur / To display error messages

// Constructeur de winCurrentUser / Constructor for winCurrentUser
winCurrentUser::winCurrentUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winCurrentUser)
{
    ui->setupUi(this);

    configureWindow();       // Configurer la fenêtre au démarrage / Configure the window on startup
    loadCurrentUserData();   // Charger les données utilisateur au démarrage / Load user data on startup

    // Connexions des boutons aux slots correspondants / Connect buttons to respective slots
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &winCurrentUser::handleCancelButtonClick);
    connect(ui->pushBtnOk, &QPushButton::clicked, this, &winCurrentUser::handleOkButtonClick);
}

// Configurer la fenêtre : taille fixe et désactiver les boutons de contrôle / Configure window: fixed size and disable control buttons
void winCurrentUser::configureWindow()
{
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Désactiver les boutons agrandir, rétrécir et fermer / Disable maximize, minimize, and close buttons
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
}

// Charger les données utilisateur dans les champs de saisie pour le dossier en cours / Load user data into input fields for the current folder
void winCurrentUser::loadCurrentUserData()
{
    int folderId = objICyamApp::getSelectedFolderId();  // Obtenir l'ID du dossier actuel / Get the current folder ID
    qDebug() << "ID du dossier courant :" << folderId;  // Debug: afficher l'ID du dossier / Debug: display folder ID
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("SELECT first_name, last_name, phone, email, addr1, addr2, addr3 FROM user WHERE id_user = :id_user AND is_deleted = 0");
    query.bindValue(":id_user", folderId);

    // Exécuter la requête et remplir les champs si elle réussit / Execute query and populate fields if successful
    if (query.exec() && query.next()) {
        ui->lineEditName->setText(query.value("last_name").toString());
        ui->lineEditFirstname->setText(query.value("first_name").toString());
        ui->lineEditPhone->setText(query.value("phone").toString());
        ui->lineEditMail->setText(query.value("email").toString());
        ui->lineEditAdr1->setText(query.value("addr1").toString());
        ui->lineEditAdr2->setText(query.value("addr2").toString());
        ui->lineEditAdr3->setText(query.value("addr3").toString());
    } else {
        // Afficher un message d'erreur en cas d'échec de chargement des données / Show an error message if data load fails
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger les données utilisateur pour ce dossier."));
        qDebug() << "Erreur SQL lors du chargement des données utilisateur:" << query.lastError();  // Debug: afficher l'erreur SQL / Debug: display SQL error
    }
}

// Mettre à jour les données utilisateur dans la base de données / Update user data in the database
void winCurrentUser::updateUserData()
{
    int folderId = objICyamApp::getSelectedFolderId();  // Obtenir l'ID du dossier actuel / Get the current folder ID
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("UPDATE user SET first_name = :first_name, last_name = :last_name, phone = :phone, "
                  "email = :email, addr1 = :addr1, addr2 = :addr2, addr3 = :addr3 WHERE id_user = :id_user");

    // Lier les champs de saisie aux paramètres SQL / Bind input fields to SQL parameters
    query.bindValue(":first_name", ui->lineEditFirstname->text());
    query.bindValue(":last_name", ui->lineEditName->text());
    query.bindValue(":phone", ui->lineEditPhone->text());
    query.bindValue(":email", ui->lineEditMail->text());
    query.bindValue(":addr1", ui->lineEditAdr1->text());
    query.bindValue(":addr2", ui->lineEditAdr2->text());
    query.bindValue(":addr3", ui->lineEditAdr3->text());
    query.bindValue(":id_user", folderId);

    // Exécuter la requête et afficher une alerte en cas d'échec / Execute the query and show an alert if it fails
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de mettre à jour les données utilisateur : %1").arg(query.lastError().text()));
    }
}

// Fermer la fenêtre sans modification / Close the window without saving changes
void winCurrentUser::handleCancelButtonClick()
{
    this->close();
}

// Enregistrer les données et fermer la fenêtre / Save data and close the window
void winCurrentUser::handleOkButtonClick()
{
    updateUserData();  // Mettre à jour les données utilisateur / Update user data in the database
    this->accept();    // Fermer la fenêtre après enregistrement / Close the window after saving
}

// Destructeur / Destructor
winCurrentUser::~winCurrentUser()
{
    delete ui;
}
