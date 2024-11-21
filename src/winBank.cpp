#include "header/winBank.h"
#include "header/objICyamApp.h"
#include "ui_winBank.h"
#include <QSqlQuery>     // Inclusion pour exécuter des requêtes SQL / Include to execute SQL queries
#include <QVariant>      // Inclusion pour utiliser QVariant dans les requêtes / Include to use QVariant in queries
#include <QMessageBox>   // Inclusion pour afficher des messages d'erreur / Include to display error messages
#include <QSqlError>     // Inclusion pour gérer les erreurs SQL / Include to handle SQL errors
#include <QDebug>        // Inclusion pour afficher des informations de débogage / Include to display debug information

// Constructeur avec paramètre pour le mode création / Constructor with creation mode parameter
winBank::winBank(bool isCreationMode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winBank)
{
    ui->setupUi(this);

    // Fixer la fenêtre pour interdire l'agrandissement / Fix window to prevent resizing
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Mettre le bouton "Supprimer" en rouge / Set the "Delete" button in red
    QPalette palette = ui->pushBtnSupp->palette();
    palette.setColor(QPalette::ButtonText, Qt::red);
    ui->pushBtnSupp->setPalette(palette);
    ui->pushBtnSupp->setVisible(false);  // Masquer le bouton "Supprimer" par défaut / Hide the "Delete" button by default

    // Charger les noms de banques dans la comboBox / Load bank names into the comboBox
    loadBankNames();

    // Connexions pour les boutons et la comboBox / Connect buttons and comboBox
    connect(ui->comboBoxBank, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winBank::onComboBoxSelectionChanged);
    connect(ui->pushBtnOK, &QPushButton::clicked, this, &winBank::handleBankOperation);
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winBank::handleBankDeletion);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &QDialog::reject);

    // Activer ou désactiver le mode création en fonction du paramètre / Enable or disable creation mode based on the parameter
    if (isCreationMode) {
        setNewBankMode();  // Forcer le mode création / Force creation mode
    }
}

// Charger les noms de banques dans la comboBox pour le dossier en cours / Load bank names into the comboBox for the current folder
void winBank::loadBankNames()
{
    ui->comboBoxBank->clear();  // Effacer la comboBox avant de la remplir / Clear comboBox before populating
    ui->comboBoxBank->addItem(tr("Nouvelle banque..."));  // Ajouter l'option de création / Add creation option

    int currentFolderId = objICyamApp::getSelectedFolderId();  // Obtenir l'ID du dossier courant / Get current folder ID

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("SELECT id_bank, bank_name FROM bank WHERE id_folder = :id_folder AND is_deleted = 0");
    query.bindValue(":id_folder", currentFolderId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des banques."));
        qDebug() << "Erreur lors de l'exécution de la requête SQL pour les banques:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString bankName = query.value(1).toString();
        ui->comboBoxBank->addItem(bankName, id);  // Ajouter chaque banque / Add each bank
    }
}

// Verrouiller la comboBox en mode "Nouvelle banque" / Lock the comboBox to "New bank" mode
void winBank::setNewBankMode()
{
    ui->comboBoxBank->setCurrentIndex(0);  // Sélectionner "Nouvelle banque..." / Select "New bank..."
    ui->comboBoxBank->setEnabled(false);   // Désactiver la comboBox / Disable the comboBox
}

// Gérer le changement de sélection dans la comboBox / Handle comboBox selection change
void winBank::onComboBoxSelectionChanged(int index)
{
    if (index == 0) {
        clearBankFields();  // Effacer les champs pour la création / Clear fields for creation mode
        toggleEditMode(true);  // Passer en mode création / Switch to creation mode
    } else {
        int bankId = ui->comboBoxBank->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("SELECT * FROM bank WHERE id_bank = :id");
        query.bindValue(":id", bankId);

        if (query.exec() && query.next()) {
            // Remplir les champs avec les données de la banque sélectionnée / Fill fields with the selected bank's data
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
        ui->pushBtnOK->setText(tr("Ok"));      // Mode création : bouton "Ok" / Creation mode: "Ok" button
        ui->pushBtnSupp->setVisible(false);    // Cacher le bouton "Supprimer" / Hide "Delete" button
    } else {
        ui->pushBtnOK->setText(tr("Modifier")); // Mode édition : bouton "Modifier" / Edit mode: "Modify" button
        ui->pushBtnSupp->setVisible(true);      // Afficher le bouton "Supprimer" / Show "Delete" button
    }
}

// Gérer la création ou la modification d'une banque / Handle bank creation or modification
void winBank::handleBankOperation()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    // Mode création : insérer une nouvelle banque / Creation mode: insert a new bank
    if (ui->comboBoxBank->currentIndex() == 0) {
        query.prepare("INSERT INTO bank (bank_name, address_line1, address_line2, address_line3, phone, email, contact_name, contact_phone, contact_email) "
                      "VALUES (:name, :adr1, :adr2, :adr3, :phone, :email, :contactName, :contactPhone, :contactEmail)");
    } else {
        // Mode édition : mettre à jour la banque existante / Edit mode: update existing bank
        int bankId = ui->comboBoxBank->currentData().toInt();
        query.prepare("UPDATE bank SET bank_name = :name, address_line1 = :adr1, address_line2 = :adr2, address_line3 = :adr3, phone = :phone, email = :email, "
                      "contact_name = :contactName, contact_phone = :contactPhone, contact_email = :contactEmail WHERE id_bank = :id AND is_deleted = 0");
        query.bindValue(":id", bankId);
    }

    // Lier les champs de saisie aux paramètres SQL / Bind input fields to SQL parameters
    query.bindValue(":name", ui->lineEditBankName->text());
    query.bindValue(":adr1", ui->lineEditBankAdr1->text());
    query.bindValue(":adr2", ui->lineEditBankAdr2->text());
    query.bindValue(":adr3", ui->lineEditBankAdr3->text());
    query.bindValue(":phone", ui->lineEditBankPhone->text());
    query.bindValue(":email", ui->lineEditBankMail->text());
    query.bindValue(":contactName", ui->lineEditContactName->text());
    query.bindValue(":contactPhone", ui->lineEditContactPhone->text());
    query.bindValue(":contactEmail", ui->lineEditContactMail->text());

    // Exécuter la requête et vérifier les erreurs / Execute the query and check for errors
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'enregistrer la banque."));
        return;
    }
    accept();  // Fermer la fenêtre après succès / Close the window upon success
}

// Gérer la suppression logique (soft delete) de la banque / Handle logical deletion (soft delete) of the bank
void winBank::handleBankDeletion()
{
    int bankId = ui->comboBoxBank->currentData().toInt();
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("UPDATE bank SET is_deleted = 1 WHERE id_bank = :id");
    query.bindValue(":id", bankId);

    // Vérifier l'exécution et afficher une confirmation / Check execution and display confirmation
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer la banque."));
        return;
    }
    QMessageBox::information(this, tr("Succès"), tr("La banque a été supprimée avec succès."));
    accept();  // Fermer la fenêtre après suppression / Close the window after deletion
}

// Effacer les champs de la banque / Clear bank fields
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

// Destructeur / Destructor
winBank::~winBank()
{
    delete ui;
}
