#include "header/winAccount.h"
#include "header/objICyamApp.h"  // Inclusion de objICyamApp pour utiliser les méthodes centralisées / Inclusion of objICyamApp for centralized methods
#include "header/winBank.h"      // Inclusion pour ouvrir la fenêtre winBank / Inclusion to open the winBank window
#include "header/winGroup.h"     // Inclusion pour ouvrir la fenêtre winGroup / Inclusion to open the winGroup window
#include "header/databaseManager.h"
#include "ui_winAccount.h"
#include <QMessageBox>           // Inclusion pour afficher des messages d'erreur / For displaying error messages
#include <QSqlError>             // Inclusion pour gérer les erreurs SQL / For handling SQL errors
#include <QCloseEvent>           // Inclusion pour gérer l'événement de fermeture / For handling close events

// Constructeur de la classe winAccount / Constructor for winAccount class
winAccount::winAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winAccount)
{
    ui->setupUi(this);

    // Configurer la fenêtre pour empêcher l'agrandissement / Set up the window to prevent resizing
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Désactiver les boutons agrandir, rétrécir et fermer / Disable maximize, minimize, and close buttons
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);

    // Masquer le bouton "Supprimer" par défaut et le rendre rouge / Hide "Delete" button by default and set it to red
    ui->pushBtnSupp->setVisible(false);
    QPalette paletteRed = ui->pushBtnSupp->palette();
    paletteRed.setColor(QPalette::ButtonText, Qt::red);
    ui->pushBtnSupp->setPalette(paletteRed);

    // Connexions des boutons et des éléments de l'interface / Connect buttons and interface elements
    connect(ui->comboBoxAccount, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winAccount::onComboBoxAccountSelectionChanged);
    connect(ui->pushBtnOk, &QPushButton::clicked, this, &winAccount::handleOkButtonClick);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &winAccount::handleCancelButtonClick);
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winAccount::handleDeleteButtonClick);
    connect(ui->pushBtnAddBank, &QPushButton::clicked, this, &winAccount::handleAddBankButtonClick);
    connect(ui->pushBtnAddGroup, &QPushButton::clicked, this, &winAccount::handleAddGroupButtonClick);

    // Chargement des données dans les ComboBox / Load data into ComboBoxes
    loadComboBoxAccount();
    loadComboBoxAccountBank();
    loadComboBoxAccountDevise();
    loadComboBoxAccountType();
    loadComboBoxAccountGroup();

    // Par défaut, désactiver certaines fonctionnalités pour la création / By default, disable certain features for creation
    setEditMode(false);
}

// Définir le mode de la fenêtre (création ou modification) / Set the window mode (creation or editing)
void winAccount::setWindowMode(bool isCreation)
{
    if (isCreation) {
        clearFields();  // Effacer les champs pour le mode Création / Clear fields for creation mode
        setEditMode(false);  // Basculer en mode Création / Switch to creation mode
    } else {
        setEditMode(true);   // Basculer en mode Modification / Switch to edit mode
    }
}

// Empêcher la fermeture de la fenêtre / Prevent the window from closing
void winAccount::closeEvent(QCloseEvent *event)
{
    event->ignore();  // Ignorer l'événement de fermeture / Ignore the close event
}

// Charger les comptes dans la ComboBox / Load accounts into the ComboBox
void winAccount::loadComboBoxAccount()
{
    ui->comboBoxAccount->clear();
    ui->comboBoxAccount->addItem(tr("Nouveau Compte..."));  // Ajouter l'option de création / Add creation option

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    if (query.exec("SELECT id_account, account_name FROM account WHERE is_deleted = 0")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString accountNumber = query.value(1).toString();
            ui->comboBoxAccount->addItem(accountNumber, id);  // Ajouter les comptes existants / Add existing accounts
        }
    }
}

// Charger les banques disponibles dans la ComboBox pour le dossier courant / Load available banks in the ComboBox for the current folder
void winAccount::loadComboBoxAccountBank()
{
    ui->comboBoxAccountBank->clear();
    int currentFolderId = objICyamApp::getSelectedFolderId(); // Obtenir l'ID du dossier courant / Get current folder ID

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("SELECT id_bank, bank_name FROM bank WHERE id_folder = :id_folder AND is_deleted = 0");
    query.bindValue(":id_folder", currentFolderId);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString bankName = query.value(1).toString();
            ui->comboBoxAccountBank->addItem(bankName, id);  // Ajouter les banques existantes pour le dossier / Add existing banks for the folder
        }
    } else {
        qDebug() << "Erreur lors de la récupération des banques pour le dossier ID" << currentFolderId << ":" << query.lastError();
    }
}

// Charger les groupes dans la ComboBox pour le dossier en cours / Load groups in the ComboBox for the current folder
void winAccount::loadComboBoxAccountGroup()
{
    ui->comboBoxAccountGroup->clear();
    int currentFolderId = objICyamApp::getSelectedFolderId(); // Obtenir l'ID du dossier courant / Get current folder ID

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("SELECT id_group, name_group FROM group_account WHERE id_folder = :id_folder AND is_deleted = 0");
    query.bindValue(":id_folder", currentFolderId);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString groupName = query.value(1).toString();
            ui->comboBoxAccountGroup->addItem(groupName, id);  // Ajouter les groupes existants pour le dossier / Add existing groups for the folder
        }
    } else {
        qDebug() << "Erreur lors de la récupération des groupes pour le dossier ID" << currentFolderId << ":" << query.lastError();
    }
}

// Charger les devises dans la ComboBox (désactivé par défaut) / Load currencies in the ComboBox (disabled by default)
void winAccount::loadComboBoxAccountDevise()
{
    ui->comboBoxAccountDevise->setEnabled(false);  // Désactiver la ComboBox pour les devises / Disable the ComboBox for currencies
}

// Charger les types de comptes dans la ComboBox / Load account types in the ComboBox
void winAccount::loadComboBoxAccountType()
{
    ui->comboBoxAccountType->clear();  // Effacer la ComboBox avant de la remplir / Clear the ComboBox before populating
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));

    if (query.exec("SELECT id_type, name_type FROM type_account WHERE is_deleted = 0")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString typeName = query.value(1).toString();
            ui->comboBoxAccountType->addItem(typeName, id);  // Ajouter chaque type de compte / Add each account type
        }
    } else {
        qDebug() << "Erreur lors de la récupération des types de comptes:" << query.lastError();
    }
}

// Effacer tous les champs pour la création d'un nouveau compte / Clear all fields for creating a new account
void winAccount::clearFields()
{
    ui->lineEditAccountName->clear();
    ui->lineEditAccountNumber->clear();
    ui->lineEditBalance->setText("0.00");  // Initialiser le solde à 0.00 / Initialize balance to 0.00
    ui->textEditDesc->clear();
    ui->lineEditContactName->clear();
    ui->lineEditContactPhone->clear();
    ui->lineEditContactMail->clear();
}

// Basculer entre les modes Création et Modification / Toggle between Creation and Edit modes
void winAccount::setEditMode(bool isEdit)
{
    if (isEdit) {
        ui->pushBtnOk->setText(tr("Modifier"));  // Passer en mode édition / Switch to edit mode
        ui->pushBtnSupp->setVisible(true);       // Rendre le bouton "Supprimer" visible / Show the "Delete" button
    } else {
        ui->pushBtnOk->setText(tr("Ok"));  // Passer en mode création / Switch to creation mode
        ui->pushBtnSupp->setVisible(false); // Masquer le bouton "Supprimer" / Hide the "Delete" button
    }
}

// Gestion du bouton OK pour créer ou modifier un compte / Handle OK button for creating or editing an account
void winAccount::handleOkButtonClick()
{
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));

    if (ui->comboBoxAccount->currentIndex() == 0) {
        // Mode création : insérer un nouveau compte bancaire / Creation mode: insert a new bank account
        query.prepare("INSERT INTO account (account_number, account_name, id_bank, id_type, id_user, balance, description, contact_name, contact_phone, contact_email) "
                      "VALUES (:number, :name, :bank, :type, :user, :balance, :description, :contact_name, :contact_phone, :contact_email)");
        query.bindValue(":user", objICyamApp::getSelectedFolderId());
    } else {
        int accountId = ui->comboBoxAccount->currentData().toInt();
        query.prepare("UPDATE account SET account_number = :number, account_name = :name, id_bank = :bank, id_type = :type, id_user = :user, balance = :balance, "
                      "description = :description, contact_name = :contact_name, contact_phone = :contact_phone, contact_email = :contact_email "
                      "WHERE id_account = :id");
        query.bindValue(":id", accountId);
        query.bindValue(":user", objICyamApp::getSelectedFolderId());
    }

    query.bindValue(":number", ui->lineEditAccountNumber->text());
    query.bindValue(":name", ui->lineEditAccountName->text());
    query.bindValue(":bank", ui->comboBoxAccountBank->currentData());
    query.bindValue(":type", ui->comboBoxAccountType->currentData());
    query.bindValue(":balance", ui->lineEditBalance->text().toDouble());
    query.bindValue(":description", ui->textEditDesc->toPlainText());
    query.bindValue(":contact_name", ui->lineEditContactName->text());
    query.bindValue(":contact_phone", ui->lineEditContactPhone->text());
    query.bindValue(":contact_email", ui->lineEditContactMail->text());

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'enregistrer le compte : %1").arg(query.lastError().text()));
        return;
    }

    accept();  // Fermer la fenêtre après succès / Close the window after success
}

// Gérer le bouton "Annuler" / Handle "Cancel" button
void winAccount::handleCancelButtonClick()
{
    reject();  // Fermer la fenêtre sans enregistrer / Close the window without saving
}

// Gérer le bouton "Supprimer" pour supprimer un compte et ses transactions associées / Handle "Delete" button to delete an account and its associated transactions
void winAccount::handleDeleteButtonClick()
{
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    int accountId = ui->comboBoxAccount->currentData().toInt();

    query.prepare("UPDATE account SET is_deleted = 1 WHERE id_account = :id");
    query.bindValue(":id", accountId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le compte : %1").arg(query.lastError().text()));
        return;
    }

    // Supprimer les transactions et ventilations associées / Delete associated transactions and splits
    QSqlQuery transQuery(QSqlDatabase::database("ICyamConnection"));
    transQuery.prepare("UPDATE transactions SET is_deleted = 1 WHERE id_account = :id_account");
    transQuery.bindValue(":id_account", accountId);
    if (!transQuery.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les transactions liées au compte."));
        return;
    }

    QSqlQuery splitQuery(QSqlDatabase::database("ICyamConnection"));
    splitQuery.prepare("UPDATE transaction_splits SET is_deleted = 1 WHERE id_transaction IN (SELECT id_transaction FROM transactions WHERE id_account = :id_account)");
    splitQuery.bindValue(":id_account", accountId);
    if (!splitQuery.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer les ventilations de transactions liées au compte."));
        return;
    }

    accept();  // Fermer la fenêtre après suppression réussie / Close the window after successful deletion
}

// Gérer la sélection d'un compte dans la ComboBox / Handle account selection in the ComboBox
void winAccount::onComboBoxAccountSelectionChanged(int index)
{
    if (index == 0) {
        clearFields();
        setEditMode(false);  // Mode création / Creation mode
    } else {
        int accountId = ui->comboBoxAccount->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
        query.prepare("SELECT account_name, id_bank, id_type, id_group, id_devises, balance, description, contact_name, contact_phone, contact_email "
                      "FROM account WHERE id_account = :id AND is_deleted = 0");
        query.bindValue(":id", accountId);

        if (query.exec() && query.next()) {
            ui->lineEditAccountName->setText(query.value("account_name").toString());
            ui->lineEditBalance->setText(QString::number(query.value("balance").toDouble()));
            ui->textEditDesc->setPlainText(query.value("description").toString());
            ui->lineEditContactName->setText(query.value("contact_name").toString());
            ui->lineEditContactPhone->setText(query.value("contact_phone").toString());
            ui->lineEditContactMail->setText(query.value("contact_email").toString());

            // Sélectionner les éléments associés dans les ComboBox / Select associated items in ComboBoxes
            selectComboBoxItemById(ui->comboBoxAccountBank, query.value("id_bank").toInt());
            selectComboBoxItemById(ui->comboBoxAccountType, query.value("id_type").toInt());
            selectComboBoxItemById(ui->comboBoxAccountGroup, query.value("id_group").toInt());
            selectComboBoxItemById(ui->comboBoxAccountDevise, query.value("id_devises").toInt());
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger les détails du compte sélectionné."));
            qDebug() << "Erreur SQL lors du chargement des détails du compte:" << query.lastError();
        }
        setEditMode(true);  // Mode modification / Edit mode
    }
}

// Sélectionner un élément dans une ComboBox en fonction de son ID / Select an item in a ComboBox by its ID
void winAccount::selectComboBoxItemById(QComboBox *comboBox, int id)
{
    for (int i = 0; i < comboBox->count(); ++i) {
        if (comboBox->itemData(i).toInt() == id) {
            comboBox->setCurrentIndex(i);
            break;
        }
    }
}

// Gérer l'ajout d'une nouvelle banque en ouvrant winBank / Handle adding a new bank by opening winBank
void winAccount::handleAddBankButtonClick()
{
    winBank *bankWindow = new winBank(true, this);
    connect(bankWindow, &QDialog::accepted, this, &winAccount::updateBankComboBoxAfterCreation);
    bankWindow->exec();
}

// Gérer l'ajout d'un nouveau groupe en ouvrant winGroup / Handle adding a new group by opening winGroup
void winAccount::handleAddGroupButtonClick()
{
    winGroup *groupWindow = new winGroup(true, this);
    connect(groupWindow, &QDialog::accepted, this, &winAccount::updateGroupComboBoxAfterCreation);
    groupWindow->exec();
}

// Mettre à jour la ComboBox des banques après création / Update bank ComboBox after creation
void winAccount::updateBankComboBoxAfterCreation()
{
    loadComboBoxAccountBank();
    int newBankId = databaseManager::getLastInsertedBankId();
    int index = ui->comboBoxAccountBank->findData(newBankId);
    if (index != -1) {
        ui->comboBoxAccountBank->setCurrentIndex(index);
    }
}

// Mettre à jour la ComboBox des groupes après création / Update group ComboBox after creation
void winAccount::updateGroupComboBoxAfterCreation()
{
    loadComboBoxAccountGroup();
    int newGroupId = databaseManager::getLastInsertedGroupId();
    int index = ui->comboBoxAccountGroup->findData(newGroupId);
    if (index != -1) {
        ui->comboBoxAccountGroup->setCurrentIndex(index);
    }
}

// Destructeur pour libérer les ressources / Destructor to free resources
winAccount::~winAccount()
{
    delete ui;
}
