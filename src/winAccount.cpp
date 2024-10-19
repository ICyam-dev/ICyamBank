#include "header/winAccount.h"
#include "ui_winAccount.h"
#include "header/winDoc.h"      // Inclusion pour la gestion de la fenêtre winDoc / Including winDoc window
#include "header/winBank.h"
#include "header/winGroup.h"
#include <QFileDialog>          // Inclusion pour ouvrir une boîte de dialogue pour les fichiers / File dialog for file selection
#include <QDir>                 // Inclusion pour manipuler les dossiers / Directory manipulation
#include <QDateTime>            // Inclusion pour manipuler les dates et heures / DateTime manipulation
#include <QSqlQuery>            // Inclusion pour exécuter des requêtes SQL / SQL queries
#include <QSqlError>            // Inclusion pour gérer les erreurs SQL / Handling SQL errors
#include <QMessageBox>          // Inclusion pour afficher des messages d'erreur / Display error messages

winAccount::winAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winAccount)
{
    ui->setupUi(this);

    // Assignation des boutons à des variables pour une meilleure lisibilité / Assigning buttons to variables for better readability
    pushBtnAddBank = ui->pushBtnAddBank;
    pushBtnAddGroup = ui->pushBtnAddGroup;
    pushBtnAddDoc = ui->pushBtnAddDoc;

    // Définir la checkbox comme widget avec le focus / Set the checkbox as the widget with the focus
    ui->checkBoxBalanceGroup->setFocus();  // Assigner le focus à la checkbox dans l'onglet Groupe / Assign focus to the checkbox in the Group tab

    // Empêcher l'agrandissement, le rétrécissement et la fermeture avec les boutons du haut / Disable resizing and closing with the top control buttons
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());  // Fixer la taille de la fenêtre / Set the window size

    // Par défaut, rendre invisible le bouton "Supprimer" et le mettre en rouge / By default, hide the "Supprimer" button and set it to red
    ui->pushBtnSupp->setVisible(false);
    QPalette paletteRed = ui->pushBtnSupp->palette();
    paletteRed.setColor(QPalette::ButtonText, Qt::red);  // Définir la couleur du texte en rouge / Set the text color to red
    ui->pushBtnSupp->setPalette(paletteRed);  // Appliquer la palette rouge au bouton / Apply the red palette to the button

    // Ne pas utiliser de couleur de fond spécifique pour les boutons "Add" / Use no specific background color for the "Add" buttons
    pushBtnAddBank->setStyleSheet("background-color: none;");
    pushBtnAddGroup->setStyleSheet("background-color: none;");
    pushBtnAddDoc->setStyleSheet("background-color: none;");

    // Désactiver le bouton "Supprimer document" par défaut / Disable the "Remove Document" button by default
    ui->pushBtnRenoveDoc->setEnabled(false);

    // Le bouton "Ok" peut changer de texte, par défaut il est "Ok" (traduisible) / The "Ok" button text can change, by default it is "Ok" (translatable)
    ui->pushBtnOk->setText(tr("Ok"));

    // Activer par défaut l'onglet "tabAccountAdmin" / Set "tabAccountAdmin" as the default active tab
    ui->tabWidget->setCurrentWidget(ui->tabAccountAdmin);

    // Connexion du bouton "Annuler" pour fermer la fenêtre / Connect the "Cancel" button to close the window
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &QDialog::reject);

    // Charger les données dans les ComboBox / Load data into ComboBoxes
    loadComboBoxAccount();
    loadComboBoxAccountBank();
    loadComboBoxAccountGroup();
}

// Méthode pour charger les comptes dans la comboBox / Method to load accounts into the ComboBox
void winAccount::loadComboBoxAccount()
{
    ui->comboBoxAccount->clear();
    ui->comboBoxAccount->addItem(tr("Nouveau Compte"));  // Ajouter une entrée "Nouveau Compte" / Add "New Account" entry

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (!query.exec("SELECT id_account, account_name FROM account WHERE is_deleted = 0")) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des comptes."));
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString accountName = query.value(1).toString();
        ui->comboBoxAccount->addItem(accountName, id);  // Ajouter les comptes à la ComboBox avec leur ID / Add accounts to the ComboBox with their ID
    }
}

// Méthode pour charger les banques dans la comboBox / Method to load banks into the ComboBox
void winAccount::loadComboBoxAccountBank()
{
    ui->comboBoxAccountBank->clear();

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (!query.exec("SELECT id_bank, bank_name FROM bank WHERE is_deleted = 0")) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des banques."));
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString bankName = query.value(1).toString();
        ui->comboBoxAccountBank->addItem(bankName, id);  // Ajouter les banques à la ComboBox avec leur ID / Add banks to the ComboBox with their ID
    }
}

// Méthode pour charger les groupes de comptes dans la comboBox / Method to load account groups into the ComboBox
void winAccount::loadComboBoxAccountGroup()
{
    ui->comboBoxAccountGroup->clear();

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (!query.exec("SELECT id_group, name_group FROM group_account")) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des groupes."));
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString groupName = query.value(1).toString();
        ui->comboBoxAccountGroup->addItem(groupName, id);  // Ajouter les groupes de comptes à la ComboBox avec leur ID / Add account groups to the ComboBox with their ID
    }
}

// Slot pour gérer le clic sur le bouton "Ajouter Banque" / Slot to handle the "Add Bank" button click
void winAccount::on_pushBtnAddBank_clicked()
{
    // Passer en mode création de banque lors de l'ouverture de la fenêtre / Open winBank in creation mode
    winBank bankDialog(true, this);  // Transmettre true pour activer le mode création / Pass true to enable creation mode

    if (bankDialog.exec() == QDialog::Accepted) {
        loadComboBoxAccountBank();  // Recharger la comboBox des banques après création / Reload the bank ComboBox after creation
        ui->comboBoxAccountBank->setCurrentIndex(ui->comboBoxAccountBank->count() - 1);  // Sélectionner la nouvelle banque / Select the newly created bank
    }
}

// Slot pour gérer le clic sur le bouton "Ajouter Groupe" / Slot to handle the "Add Group" button click
void winAccount::on_pushBtnAddGroup_clicked()
{
    // Création d'une instance de winGroup / Create an instance of winGroup
    winGroup groupDialog(this);

    // Activer le mode "Création" en désactivant la comboBox / Activate "Creation" mode by disabling the comboBox
    groupDialog.setNewGroupMode();  // Appel de la méthode pour forcer le mode création

    // Afficher la fenêtre winGroup en modal / Show the winGroup window in modal mode
    if (groupDialog.exec() == QDialog::Accepted) {
        // Si la fenêtre est validée, recharger les groupes dans la comboBox / If the window is accepted, reload the groups in the ComboBox
        loadComboBoxAccountGroup();
        ui->comboBoxAccountGroup->setCurrentIndex(ui->comboBoxAccountGroup->count() - 1);  // Sélectionner le nouveau groupe créé
    }
}

// Bouton pour ajouter un document / Button to add a document
void winAccount::on_pushBtnAddDoc_clicked()
{
    // Ouvrir une boîte de dialogue pour sélectionner un fichier (documents ou images uniquement)
    QString filePath = QFileDialog::getOpenFileName(this, tr("Sélectionnez un document"),
                                                    QDir::homePath(),
                                                    tr("Documents (*.pdf *.doc *.docx *.png *.jpg)"));

    if (filePath.isEmpty()) {
        return; // Si l'utilisateur annule la sélection, ne rien faire / If user cancels, do nothing
    }

    // Créer le dossier _docs s'il n'existe pas / Create _docs folder if it doesn't exist
    QString docsDir = QDir(QSqlDatabase::database("ICyamBankConnection").databaseName()).absolutePath() + "/_docs";
    QDir().mkpath(docsDir);

    // Renommer le fichier en utilisant le format AAMMJJHHmmss.ext / Rename the file using AAMMJJHHmmss.ext format
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    QString fileExtension = QFileInfo(filePath).suffix();
    QString newFileName = timestamp + "." + fileExtension;
    QString newFilePath = docsDir + "/" + newFileName;

    // Copier le fichier dans le dossier _docs avec le nouveau nom / Copy the file to _docs with the new name
    if (!QFile::copy(filePath, newFilePath)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de copier le fichier."));
        return;
    }

    // Ouvrir la fenêtre winDoc pour entrer le nom et la description du document / Open winDoc to enter name and description
    winDoc docDialog(this);
    if (docDialog.exec() == QDialog::Accepted) {
        QString docName = docDialog.getDocName();  // Utilisation d'un getter public pour obtenir le nom du document / Use public getter to retrieve document name
        QString docDescription = docDialog.getDocDescription();  // Utilisation d'un getter public pour obtenir la description du document / Use public getter to retrieve document description

        // Insérer le document dans la base de données / Insert the document into the database
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("INSERT INTO account_docs (id_account, doc_name, doc_url, doc_description) "
                      "VALUES (:id_account, :doc_name, :doc_url, :doc_description)");
        query.bindValue(":id_account", currentAccountId);  // Assurez-vous que currentAccountId est l'ID du compte actuel / Make sure currentAccountId is the current account ID
        query.bindValue(":doc_name", docName);
        query.bindValue(":doc_url", newFilePath);  // Utilisez le chemin absolu du fichier / Use the absolute path of the file
        query.bindValue(":doc_description", docDescription);

        if (!query.exec()) {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ajouter le document."));
            qDebug() << "Erreur SQL lors de l'ajout du document:" << query.lastError();
            return;
        }

        // Mettre à jour la liste des documents après l'ajout / Update the document list after adding
        updateDocumentList();
    }
}

// Fonction pour mettre à jour la liste des documents associés à un compte
void winAccount::updateDocumentList()
{
    // Effacer la liste actuelle des documents / Clear the current document list
    ui->listAccountDoc->clear();

    // Requête pour récupérer les documents liés au compte actuel / Query to retrieve documents linked to the current account
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("SELECT doc_name, doc_url FROM account_docs WHERE id_account = :id_account");
    query.bindValue(":id_account", currentAccountId);  // ID du compte actuel / Current account ID

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer les documents associés au compte."));
        return;
    }

    while (query.next()) {
        QString docName = query.value(0).toString();
        QString docUrl = query.value(1).toString();

        // Ajouter le nom du document à la liste / Add the document name to the list
        QListWidgetItem *item = new QListWidgetItem(docName, ui->listAccountDoc);
        item->setData(Qt::UserRole, docUrl);  // Stocker l'URL du document pour une utilisation ultérieure / Store the document URL for later use
    }
}

void winAccount::closeEvent(QCloseEvent *event)
{
    // Empêcher la fermeture de la fenêtre / Prevent the window from being closed
    event->ignore();  // Ignorer l'événement de fermeture / Ignore the close event
}

void winAccount::on_pushBtnCancel_clicked()
{
    // Fermer la fenêtre sans sauvegarder / Close the window without saving
    this->reject();  // Rejeter et fermer la fenêtre / Reject and close the window
}

void winAccount::on_pushBtnOk_clicked()
{
    saveAccountData();  // Appeler la méthode pour enregistrer ou modifier les données / Call the method to save or modify the data
}

void winAccount::saveAccountData()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    // Vérifier si on est en mode "Création" ou "Modification"
    // Check if we are in "Creation" or "Modification" mode
    if (ui->comboBoxAccount->currentIndex() == 0) {
        // Mode création : insérer un nouveau compte bancaire
        // Creation mode: insert a new bank account
        query.prepare("INSERT INTO account (account_number, id_user, id_bank, id_type, id_group, balance, description, opening_date, active, contact_name, contact_phone, contact_email, icon_url) "
                      "VALUES (:number, :user, :bank, :type, :group, :balance, :description, :opening_date, :active, :contact_name, :contact_phone, :contact_email, :icon_url)");
    } else {
        // Mode modification : mise à jour du compte existant
        // Modification mode: update the existing account
        int accountId = ui->comboBoxAccount->currentData().toInt();
        query.prepare("UPDATE account SET account_number = :number, id_user = :user, id_bank = :bank, id_type = :type, id_group = :group, "
                      "balance = :balance, description = :description, opening_date = :opening_date, active = :active, "
                      "contact_name = :contact_name, contact_phone = :contact_phone, contact_email = :contact_email, icon_url = :icon_url "
                      "WHERE id_account = :id");
        query.bindValue(":id", accountId);
    }

    // Lier les données de l'interface utilisateur aux paramètres de la requête SQL
    // Bind the data from the user interface to the SQL query parameters
    query.bindValue(":number", ui->lineEditAccountNumber->text());
    query.bindValue(":user", 1); // ID utilisateur par défaut / Default user ID (change according to logic)
    query.bindValue(":bank", ui->comboBoxAccountBank->currentData());
    query.bindValue(":type", ui->comboBoxAccountType->currentData());
    query.bindValue(":group", ui->comboBoxAccountGroup->currentData());
    query.bindValue(":balance", ui->lineEditBalance->text().toDouble());
    query.bindValue(":description", ui->textEditDesc->toPlainText());
    query.bindValue(":opening_date", QDate::currentDate().toString("yyyy-MM-dd")); // Date d'ouverture du compte / Account opening date
    query.bindValue(":active", true);  // Compte actif par défaut / Account active by default
    query.bindValue(":contact_name", ui->lineEditContactName->text());
    query.bindValue(":contact_phone", ui->lineEditContactPhone->text());
    query.bindValue(":contact_email", ui->lineEditContactMail->text());
    query.bindValue(":icon_url", ""); // Icone vide pour l'instant / Empty icon for now

    // Exécuter la requête SQL
    // Execute the SQL query
    if (!query.exec()) {
        // Afficher une erreur en cas d'échec
        // Display an error if it fails
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'enregistrer le compte : %1").arg(query.lastError().text()));
        return;
    }

    // Fermer la fenêtre après enregistrement réussi
    // Close the window after successful saving
    accept();
}

void winAccount::on_pushBtnSupp_clicked()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    int accountId = ui->comboBoxAccount->currentData().toInt();

    // Supprimer logiquement les documents associés au compte
    // Soft delete the documents associated with the account
    query.prepare("UPDATE account_documents SET is_deleted = 1 WHERE id_account = :id_account");
    query.bindValue(":id_account", accountId);
    if (!query.exec()) {
        //fr : Afficher une erreur en cas d'échec de l'exécution pour les documents
        //en : Display an error if execution fails for the documents
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les documents liés au compte : %1").arg(query.lastError().text()));
        qDebug() << "Erreur SQL : " << query.lastError().text();
        return;
    }

    // Supprimer logiquement les ventilations associées aux transactions du compte
    // Soft delete the transaction splits associated with the account's transactions
    query.prepare("UPDATE transaction_splits SET is_deleted = 1 WHERE id_transaction IN (SELECT id_transaction FROM transactions WHERE id_account = :id_account)");
    query.bindValue(":id_account", accountId);
    if (!query.exec()) {
        //fr : Afficher une erreur en cas d'échec de l'exécution pour les ventilations
        //en : Display an error if execution fails for the transaction splits
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les ventilations liées au compte : %1").arg(query.lastError().text()));
        qDebug() << "Erreur SQL : " << query.lastError().text();
        return;
    }

    // Supprimer logiquement les transactions associées au compte
    // Soft delete the transactions associated with the account
    query.prepare("UPDATE transactions SET is_deleted = 1 WHERE id_account = :id_account");
    query.bindValue(":id_account", accountId);
    if (!query.exec()) {
        //fr : Afficher une erreur en cas d'échec de l'exécution pour les transactions
        //en : Display an error if execution fails for the transactions
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les transactions liées au compte : %1").arg(query.lastError().text()));
        qDebug() << "Erreur SQL : " << query.lastError().text();
        return;
    }

    // Supprimer logiquement le compte lui-même
    // Soft delete the account itself
    query.prepare("UPDATE account SET is_deleted = 1 WHERE id_account = :id_account");
    query.bindValue(":id_account", accountId);
    if (!query.exec()) {
        //fr : Afficher une erreur en cas d'échec de l'exécution pour le compte
        //en : Display an error if execution fails for the account
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le compte bancaire : %1").arg(query.lastError().text()));
        qDebug() << "Erreur SQL : " << query.lastError().text();
        return;
    }

    //fr : Afficher un message de succès
    //en : Display a success message
    QMessageBox::information(this, tr("Succès"), tr("Le compte bancaire et ses données liées ont été supprimés avec succès."));

    // Fermer la fenêtre après suppression réussie
    // Close the window after successful deletion
    accept();
}

winAccount::~winAccount()
{
    // Nettoyage des ressources de l'interface utilisateur / Cleanup of the user interface resources
    delete ui;
}
