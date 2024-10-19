#include "header/winBank.h"
#include "ui_winBank.h"
#include <QSqlQuery>     // Inclusion pour exécuter des requêtes SQL / Inclusion for executing SQL queries
#include <QVariant>      // Inclusion pour utiliser QVariant dans les requêtes / Inclusion to use QVariant in queries
#include <QMessageBox>   // Inclusion pour afficher des messages d'erreur / Inclusion to display error messages
#include <QSqlError>     // Inclusion pour gérer les erreurs SQL / Inclusion for handling SQL errors
#include <QDebug>        // Inclusion pour afficher des informations de débogage / Inclusion for debug information

// Constructeur modifié pour accepter le paramètre "isCreationMode" / Modified constructor to accept "isCreationMode" parameter
winBank::winBank(bool isCreationMode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winBank)
{
    ui->setupUi(this);

    // Interdire l'agrandissement de la fenêtre / Prevent window resizing
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Mettre le bouton "Supprimer" en rouge / Set the "Delete" button in red
    QPalette palette = ui->pushBtnSupp->palette();
    palette.setColor(QPalette::ButtonText, Qt::red);
    ui->pushBtnSupp->setPalette(palette);

    // Charger les noms de banques dans la comboBox / Load bank names into the comboBox
    loadBankNames();

    // Connexion pour détecter le changement dans la comboBox / Connect to detect comboBox selection change
    connect(ui->comboBoxBank, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winBank::onComboBoxSelectionChanged);

    // Connexion du bouton "OK" pour gérer la création ou la modification / Connect the "OK" button to handle creation or modification
    connect(ui->pushBtnOK, &QPushButton::clicked, this, &winBank::handleBankOperation);

    // Connexion du bouton "Supprimer" pour gérer la suppression logique (soft delete) / Connect the "Delete" button to handle logical deletion (soft delete)
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winBank::handleBankDeletion);

    // Désactiver le bouton "Supprimer" par défaut / Disable the "Delete" button by default
    ui->pushBtnSupp->setVisible(false);

    // Connecter le bouton "Annuler" pour fermer la fenêtre / Connect the "Cancel" button to close the window
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &QDialog::reject);

    // Activer ou désactiver le mode création en fonction du paramètre "isCreationMode" / Enable or disable creation mode based on "isCreationMode" parameter
    if (isCreationMode) {
        setNewBankMode();  // Forcer le mode création si c'est demandé / Force creation mode if requested
    }
}

// Charger les noms de banques dans la comboBox / Load bank names into the comboBox
void winBank::loadBankNames()
{
    // Effacer la comboBox avant de la remplir / Clear the comboBox before filling it
    ui->comboBoxBank->clear();

    // Ajouter l'option "Nouvelle banque..." en haut de la liste / Add "New bank..." option at the top of the list
    ui->comboBoxBank->addItem(tr("Nouvelle banque..."));

    // Requête pour récupérer les noms de banques non supprimées (is_deleted = 0) / Query to retrieve bank names that are not deleted (is_deleted = 0)
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    if (!query.exec("SELECT id_bank, bank_name FROM bank WHERE is_deleted = 0")) {
        qDebug() << "Erreur de requête SQL lors de la récupération des banques" << query.lastError();
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des banques."));
        return;
    }

    while (query.next()) {
        // Ajouter chaque banque dans la comboBox avec son ID en tant que donnée associée / Add each bank to the comboBox with its ID as associated data
        int id = query.value(0).toInt();
        QString bankName = query.value(1).toString();
        ui->comboBoxBank->addItem(bankName, id);
    }
}

// Méthode pour verrouiller la comboBox sur "Nouvelle banque"
// Method to lock the comboBox on "New Bank"
void winBank::setNewBankMode()
{
    ui->comboBoxBank->setCurrentIndex(0); // Sélectionner "Nouvelle banque..." / Select "New Bank..."
    ui->comboBoxBank->setEnabled(false);  // Désactiver la comboBox / Disable the comboBox
}

// Gérer le changement de sélection dans la comboBox / Handle comboBox selection change
void winBank::onComboBoxSelectionChanged(int index)
{
    if (index == 0) {
        // Mode création : La première option est "Nouvelle banque..." / Creation mode: First option is "New bank..."
        clearBankFields();  // Vider les champs / Clear the fields
        toggleEditMode(true);  // Activer le mode création / Enable creation mode
    } else {
        // Mode édition : Charger les informations de la banque sélectionnée / Edit mode: Load selected bank information
        int bankId = ui->comboBoxBank->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("SELECT * FROM bank WHERE id_bank = :id");
        query.bindValue(":id", bankId);

        if (query.exec() && query.next()) {
            // Remplir les champs avec les données de la banque sélectionnée / Fill the fields with the selected bank's data
            ui->lineEditBankName->setText(query.value("bank_name").toString());
            ui->lineEditBankAdr1->setText(query.value("address_line1").toString());
            ui->lineEditBankAdr2->setText(query.value("address_line2").toString());
            ui->lineEditBankAdr3->setText(query.value("address_line3").toString());
            ui->lineEditBankPhone->setText(query.value("phone").toString());
            ui->lineEditBankMail->setText(query.value("email").toString());
            ui->lineEditContactName->setText(query.value("contact_name").toString());
            ui->lineEditContactPhone->setText(query.value("contact_phone").toString());
            ui->lineEditContactMail->setText(query.value("contact_email").toString());
        }

        toggleEditMode(false);  // Passer en mode édition / Switch to edit mode
    }
}

// Basculer entre mode création et édition / Toggle between creation and edit mode
void winBank::toggleEditMode(bool isNew)
{
    if (isNew) {
        // Mode création : "Ok" et "Supprimer" caché / Creation mode: "Ok" and "Delete" hidden
        ui->pushBtnOK->setText(tr("Ok"));
        ui->pushBtnSupp->setVisible(false);
    } else {
        // Mode édition : "Modifier" et "Supprimer" visible / Edit mode: "Modify" and "Delete" visible
        ui->pushBtnOK->setText(tr("Modifier"));
        ui->pushBtnSupp->setVisible(true);
    }
}

// Gérer l'opération de création ou de modification de la banque / Handle bank creation or modification
void winBank::handleBankOperation()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    if (ui->comboBoxBank->currentIndex() == 0) {
        // Mode création / Creation mode
        query.prepare("INSERT INTO bank (bank_name, address_line1, address_line2, address_line3, phone, email, contact_name, contact_phone, contact_email) "
                      "VALUES (:name, :adr1, :adr2, :adr3, :phone, :email, :contactName, :contactPhone, :contactEmail)");
    } else {
        // Mode édition / Edit mode
        int bankId = ui->comboBoxBank->currentData().toInt();
        query.prepare("UPDATE bank SET bank_name = :name, address_line1 = :adr1, address_line2 = :adr2, address_line3 = :adr3, phone = :phone, email = :email, "
                      "contact_name = :contactName, contact_phone = :contactPhone, contact_email = :contactEmail WHERE id_bank = :id AND is_deleted = 0");
        query.bindValue(":id", bankId);
    }

    query.bindValue(":name", ui->lineEditBankName->text());
    query.bindValue(":adr1", ui->lineEditBankAdr1->text());
    query.bindValue(":adr2", ui->lineEditBankAdr2->text());
    query.bindValue(":adr3", ui->lineEditBankAdr3->text());
    query.bindValue(":phone", ui->lineEditBankPhone->text());
    query.bindValue(":email", ui->lineEditBankMail->text());
    query.bindValue(":contactName", ui->lineEditContactName->text());
    query.bindValue(":contactPhone", ui->lineEditContactPhone->text());
    query.bindValue(":contactEmail", ui->lineEditContactMail->text());

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de sauvegarder la banque."));
        qDebug() << "Erreur SQL lors de la sauvegarde de la banque:" << query.lastError();
        return;
    }

    accept();  // Fermer la fenêtre après succès / Close the window after success
}

// Gérer la suppression logique (soft delete) de la banque / Handle logical deletion (soft delete) of the bank
void winBank::handleBankDeletion()
{
    int bankId = ui->comboBoxBank->currentData().toInt();

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("UPDATE bank SET is_deleted = 1 WHERE id_bank = :id");
    query.bindValue(":id", bankId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer la banque."));
        qDebug() << "Erreur SQL lors de la suppression de la banque:" << query.lastError();
        return;
    }

    QMessageBox::information(this, tr("Succès"), tr("La banque a été supprimée avec succès."));
    accept();  // Fermer la fenêtre après suppression / Close the window after deletion
}

// Vider les champs de la banque / Clear the bank fields
void winBank::clearBankFields()
{
    ui->lineEditBankName->clear();
    ui->lineEditBankAdr1->clear();
    ui->lineEditBankAdr2->clear();
    ui->lineEditBankAdr3->clear();
    ui->lineEditBankPhone->clear();
    ui->lineEditBankMail->clear();
    ui->lineEditContactName->clear();
    ui->lineEditContactPhone->clear();
    ui->lineEditContactMail->clear();
}

// Méthode pour interdire la fermeture avec le bouton en haut à gauche / Method to prevent closing with the top-left button
void winBank::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

winBank::~winBank()
{
    delete ui;
}
