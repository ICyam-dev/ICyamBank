#include "header/databaseManager.h"
#include "header/winAccount.h"
#include "header/winBank.h"    // Inclusion pour ouvrir la fenêtre winBank
#include "header/winGroup.h"   // Inclusion pour ouvrir la fenêtre winGroup
#include "ui_winAccount.h"
#include <QMessageBox>         // Inclusion pour afficher des messages d'erreur / Include to display error messages
#include <QSqlError>           // Inclusion pour gérer les erreurs SQL / Include to handle SQL errors
#include <QCloseEvent>         // Inclusion pour gérer l'événement de fermeture / Include to handle the close event

winAccount::winAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winAccount)
{
    ui->setupUi(this);

    // Empêcher l'agrandissement et fixer la taille de la fenêtre / Prevent resizing and set the window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Désactiver les boutons agrandir, rétrécir et fermer / Disable maximize, minimize, and close buttons
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);

    // Par défaut, masquer le bouton "Supprimer" et mettre le texte en rouge / By default, hide the "Delete" button and set the text in red
    ui->pushBtnSupp->setVisible(false);
    QPalette paletteRed = ui->pushBtnSupp->palette();
    paletteRed.setColor(QPalette::ButtonText, Qt::red);
    ui->pushBtnSupp->setPalette(paletteRed);

    connect(ui->comboBoxAccount, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winAccount::onComboBoxAccountSelectionChanged);
    connect(ui->pushBtnOk, &QPushButton::clicked, this, &winAccount::handleOkButtonClick);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &winAccount::handleCancelButtonClick);
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winAccount::handleDeleteButtonClick);
    connect(ui->pushBtnAddBank, &QPushButton::clicked, this, &winAccount::handleAddBankButtonClick);
    connect(ui->pushBtnAddGroup, &QPushButton::clicked, this, &winAccount::handleAddGroupButtonClick);

    // Charger les données dans les ComboBox / Load data into ComboBoxes
    loadComboBoxAccount();
    loadComboBoxAccountBank();
    loadComboBoxAccountDevise();
    loadComboBoxAccountType();
    loadComboBoxAccountGroup();

    // Par défaut, désactiver certaines fonctionnalités pour la création / By default, disable certain functionalities for creation mode
    setEditMode(false);
}

// Méthode pour définir le mode de la fenêtre / Method to set the window mode
void winAccount::setWindowMode(bool isCreation)
{
    if (isCreation) {
        clearFields();  // Effacer les champs pour le mode Création / Clear fields for creation mode
        setEditMode(false);  // Basculer en mode Création / Switch to Creation mode
    } else {
        setEditMode(true);   // Basculer en mode Modification / Switch to Edit mode
    }
}

// Fermer l'événement de la fenêtre pour empêcher la fermeture / Override close event to prevent closing
void winAccount::closeEvent(QCloseEvent *event)
{
    event->ignore();  // Ignorer l'événement de fermeture / Ignore the close event
}

// Charger les comptes dans la ComboBox / Load accounts into the ComboBox
void winAccount::loadComboBoxAccount()
{
    ui->comboBoxAccount->clear();
    ui->comboBoxAccount->addItem(tr("Nouveau Compte..."));  // Ajouter l'option de création / Add creation option

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (query.exec("SELECT id_account, account_name FROM account WHERE is_deleted = 0")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString accountNumber = query.value(1).toString();
            ui->comboBoxAccount->addItem(accountNumber, id);  // Ajouter les comptes existants / Add existing accounts
        }
    }
}

// Charger les banques dans la ComboBox / Load banks into the ComboBox
void winAccount::loadComboBoxAccountBank()
{
    ui->comboBoxAccountBank->clear();
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (query.exec("SELECT id_bank, bank_name FROM bank")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString bankName = query.value(1).toString();
            ui->comboBoxAccountBank->addItem(bankName, id);  // Ajouter les banques existantes / Add existing banks
        }
    }
}

// Charger les devises dans la ComboBox / Load currencies into the ComboBox
void winAccount::loadComboBoxAccountDevise()
{
    ui->comboBoxAccountDevise->setEnabled(false);  // Désactiver la ComboBox pour les devises / Disable the currency ComboBox for now
}

// Charger les types de comptes dans la ComboBox / Load account types into the ComboBox
void winAccount::loadComboBoxAccountType()
{
    ui->comboBoxAccountType->clear();  // Effacer la ComboBox avant de la remplir / Clear the ComboBox before populating
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    // Requête pour récupérer les types de compte actifs / Query to retrieve active account types
    if (query.exec("SELECT id_type, name_type FROM type_account WHERE is_deleted = 0")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString typeName = query.value(1).toString();
            ui->comboBoxAccountType->addItem(typeName, id);  // Ajouter chaque type de compte à la ComboBox / Add each account type to the ComboBox
        }
    } else {
        qDebug() << "Erreur lors de la récupération des types de comptes:" << query.lastError();  // Afficher une erreur en cas d'échec / Show an error if the query fails
    }
}

// Effacer tous les champs pour la création d'un nouveau compte / Clear all fields for creating a new account
void winAccount::clearFields()
{
    ui->lineEditAccountName->clear();
    ui->lineEditAccountNumber->clear();
    ui->lineEditBalance->setText("0.00");  // Initialiser le solde à 0.00 / Set balance to 0.00
    ui->textEditDesc->clear();
    ui->lineEditContactName->clear();
    ui->lineEditContactPhone->clear();
    ui->lineEditContactMail->clear();
}

// Basculer entre les modes Création et Modification / Switch between Creation and Edit modes
void winAccount::setEditMode(bool isEdit)
{
    if (isEdit) {
        ui->pushBtnOk->setText(tr("Modifier"));  // Passer en mode édition / Switch to edit mode
        ui->pushBtnSupp->setVisible(true);       // Rendre le bouton "Supprimer" visible / Make the "Delete" button visible
    } else {
        ui->pushBtnOk->setText(tr("Ok"));  // Passer en mode création / Switch to creation mode
        ui->pushBtnSupp->setVisible(false); // Masquer le bouton "Supprimer" / Hide the "Delete" button
    }
}

// Gestion du bouton OK (Créer ou Modifier un compte) / Handle the OK button (Create or Modify an account)
void winAccount::handleOkButtonClick()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    if (ui->comboBoxAccount->currentIndex() == 0) {
        // Mode création : insérer un nouveau compte bancaire / Creation mode: insert a new bank account
        query.prepare("INSERT INTO account (account_number, account_name, id_bank, id_type, id_user, balance, description, contact_name, contact_phone, contact_email) "
                      "VALUES (:number, :name, :bank, :type, :user, :balance, :description, :contact_name, :contact_phone, :contact_email)");
        query.bindValue(":user", databaseManager::getCurrentFolderId());  // Liaison pour l'ID utilisateur en cours
    } else {
        // Mode modification : mise à jour du compte existant / Edit mode: update the existing bank account
        int accountId = ui->comboBoxAccount->currentData().toInt();
        query.prepare("UPDATE account SET account_number = :number, account_name = :name, id_bank = :bank, id_type = :type, id_user = :user, balance = :balance, "
                      "description = :description, contact_name = :contact_name, contact_phone = :contact_phone, contact_email = :contact_email "
                      "WHERE id_account = :id");
        query.bindValue(":id", accountId);
        query.bindValue(":user", databaseManager::getCurrentFolderId());  // Assurez-vous que l'ID utilisateur est bien lié en mode modification aussi
    }

    // Lier les autres champs de saisie aux paramètres SQL / Bind other input fields to SQL parameters
    query.bindValue(":number", ui->lineEditAccountNumber->text());
    query.bindValue(":name", ui->lineEditAccountName->text());
    query.bindValue(":bank", ui->comboBoxAccountBank->currentData());
    query.bindValue(":type", ui->comboBoxAccountType->currentData());
    query.bindValue(":balance", ui->lineEditBalance->text().toDouble());
    query.bindValue(":description", ui->textEditDesc->toPlainText());
    query.bindValue(":contact_name", ui->lineEditContactName->text());
    query.bindValue(":contact_phone", ui->lineEditContactPhone->text());
    query.bindValue(":contact_email", ui->lineEditContactMail->text());

    // Exécuter la requête et vérifier les erreurs / Execute the query and check for errors
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'enregistrer le compte : %1").arg(query.lastError().text()));
        return;
    }

    accept();  // Fermer la fenêtre après succès / Close the window after success
}

// Gestion du bouton Annuler / Handle the Cancel button
void winAccount::handleCancelButtonClick()
{
    reject();  // Fermer la fenêtre sans enregistrer / Close the window without saving
}

// Gestion du bouton Supprimer / Handle the Delete button
void winAccount::handleDeleteButtonClick()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    int accountId = ui->comboBoxAccount->currentData().toInt();

    // Soft delete : mise à jour du flag "is_deleted" / Soft delete: update the "is_deleted" flag
    query.prepare("UPDATE account SET is_deleted = 1 WHERE id_account = :id");
    query.bindValue(":id", accountId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le compte : %1").arg(query.lastError().text()));
        return;
    }

    // Suppression en cascade des transactions et des ventilations / Cascading delete for transactions and splits
    QSqlQuery transQuery(QSqlDatabase::database("ICyamBankConnection"));
    transQuery.prepare("UPDATE transactions SET is_deleted = 1 WHERE id_account = :id_account");
    transQuery.bindValue(":id_account", accountId);
    if (!transQuery.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les transactions liées au compte."));
        return;
    }

    // Suppression en cascade des ventilations de transactions / Cascading delete for transaction splits
    QSqlQuery splitQuery(QSqlDatabase::database("ICyamBankConnection"));
    splitQuery.prepare("UPDATE transaction_splits SET is_deleted = 1 WHERE id_transaction IN (SELECT id_transaction FROM transactions WHERE id_account = :id_account)");
    splitQuery.bindValue(":id_account", accountId);
    if (!splitQuery.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les ventilations de transactions liées au compte."));
        return;
    }

    accept();  // Fermer la fenêtre après suppression réussie / Close the window after successful deletion
}

void winAccount::onComboBoxAccountSelectionChanged(int index)
{
    if (index == 0) {
        // Mode Création
        clearFields();
        setEditMode(false);
    } else {
        // Mode Modification pour un compte existant
        int accountId = ui->comboBoxAccount->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("SELECT account_name, id_bank, id_type, id_group, id_devises, balance, description, contact_name, contact_phone, contact_email "
                      "FROM account WHERE id_account = :id AND is_deleted = 0");
        query.bindValue(":id", accountId);

        if (query.exec() && query.next()) {
            // Remplissage des champs
            ui->lineEditAccountName->setText(query.value("account_name").toString());
            ui->lineEditBalance->setText(QString::number(query.value("balance").toDouble()));
            ui->textEditDesc->setPlainText(query.value("description").toString());
            ui->lineEditContactName->setText(query.value("contact_name").toString());
            ui->lineEditContactPhone->setText(query.value("contact_phone").toString());
            ui->lineEditContactMail->setText(query.value("contact_email").toString());

            // Sélectionner le bon élément dans chaque ComboBox
            int bankId = query.value("id_bank").toInt();
            int typeId = query.value("id_type").toInt();
            int groupId = query.value("id_group").toInt();
            int deviseId = query.value("id_devises").toInt();

            selectComboBoxItemById(ui->comboBoxAccountBank, bankId);
            selectComboBoxItemById(ui->comboBoxAccountType, typeId);
            selectComboBoxItemById(ui->comboBoxAccountGroup, groupId);
            selectComboBoxItemById(ui->comboBoxAccountDevise, deviseId);
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger les détails du compte sélectionné."));
            qDebug() << "Erreur SQL lors du chargement des détails du compte:" << query.lastError();
        }
        setEditMode(true);  // Activer le mode modification
    }
}

// Fonction pour sélectionner l'élément correspondant à l'ID dans une ComboBox
void winAccount::selectComboBoxItemById(QComboBox *comboBox, int id)
{
    for (int i = 0; i < comboBox->count(); ++i) {
        if (comboBox->itemData(i).toInt() == id) {
            comboBox->setCurrentIndex(i);
            break;
        }
    }
}

void winAccount::handleAddBankButtonClick() {
    // Créer une instance de winBank en mode création forcée

    winBank *bankWindow = new winBank(true, this);  // Mode création forcée
    connect(bankWindow, &QDialog::accepted, this, &winAccount::updateBankComboBoxAfterCreation);
    bankWindow->exec();

}

void winAccount::handleAddGroupButtonClick() {
    // Créer une instance de winGroup en mode création forcée

    winGroup *groupWindow = new winGroup(true, this);  // Mode création forcée
    connect(groupWindow, &QDialog::accepted, this, &winAccount::updateGroupComboBoxAfterCreation);
    groupWindow->exec();

}

// Mise à jour de la ComboBox après création d'une nouvelle banque
void winAccount::updateBankComboBoxAfterCreation()
{
    loadComboBoxAccountBank();  // Recharger les banques dans la ComboBox
    int newBankId = databaseManager::getLastInsertedBankId();  // Récupérer l'ID de la dernière banque créée
    int index = ui->comboBoxAccountBank->findData(newBankId);  // Trouver l'index correspondant dans la ComboBox
    if (index != -1) {
        ui->comboBoxAccountBank->setCurrentIndex(index);  // Sélectionner la nouvelle banque
    }
}

// Mise à jour de la ComboBox après création d'un nouveau groupe
void winAccount::updateGroupComboBoxAfterCreation()
{
    loadComboBoxAccountGroup();  // Recharger les groupes dans la ComboBox
    int newGroupId = databaseManager::getLastInsertedGroupId();  // Récupérer l'ID du dernier groupe créé
    int index = ui->comboBoxAccountGroup->findData(newGroupId);  // Trouver l'index correspondant dans la ComboBox
    if (index != -1) {
        ui->comboBoxAccountGroup->setCurrentIndex(index);  // Sélectionner le nouveau groupe
    }
}

void winAccount::loadComboBoxAccountGroup()
{
    ui->comboBoxAccountGroup->clear();  // Efface la comboBox avant de la remplir

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (query.exec("SELECT id_group, name_group FROM group_account WHERE is_deleted = 0")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString groupName = query.value(1).toString();
            ui->comboBoxAccountGroup->addItem(groupName, id);  // Ajoute chaque groupe à la comboBox
        }
    } else {
        qDebug() << "Erreur lors du chargement des groupes de comptes:" << query.lastError();
    }
}

winAccount::~winAccount()
{
    delete ui;
}
