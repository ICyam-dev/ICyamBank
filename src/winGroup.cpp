#include "header/databaseManager.h"  // Inclusion pour accéder à currentFolderId() / Inclusion to access currentFolderId()
#include "header/winGroup.h"
#include "ui_winGroup.h"
#include <QSqlQuery>       // Inclusion pour exécuter des requêtes SQL / Inclusion for executing SQL queries
#include <QSqlError>       // Inclusion pour capturer les erreurs SQL / Inclusion to capture SQL errors
#include <QMessageBox>     // Inclusion pour afficher des messages d'erreur / Inclusion to display error messages

// Constructeur modifié pour accepter le paramètre "isCreationMode" / Modified constructor to accept "isCreationMode" parameter
winGroup::winGroup(bool isCreationMode, QWidget *parent) : QDialog(parent), ui(new Ui::winGroup)
{
    ui->setupUi(this);

    // Empêcher l'agrandissement et fixer la taille de la fenêtre / Prevent resizing and set the window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Configurer le bouton "Supprimer" en rouge et invisible par défaut / Set the "Delete" button in red and hide it by default
    QPalette palette = ui->pushBtnSupp->palette();
    palette.setColor(QPalette::ButtonText, Qt::red);
    ui->pushBtnSupp->setPalette(palette);
    ui->pushBtnSupp->setVisible(false);

    // Charger les groupes dans la comboBox / Load groups into the comboBox
    loadGroupNames();

    // Activer le mode création forcée si demandé / Enable forced creation mode if requested
    if (isCreationMode) {
        setNewGroupMode();  // Forcer le mode création / Force creation mode
    }

    // Connexion des signaux pour détecter les changements et les actions des boutons / Connect signals for detecting changes and button actions
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winGroup::onComboBoxSelectionChanged);
    connect(ui->pushBtnOK, &QPushButton::clicked, this, &winGroup::handleGroupOperation);
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winGroup::handleGroupDeletion);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// Basculer la comboBox sur "Nouveau Groupe" et verrouiller la sélection / Lock comboBox on "New Group" selection
void winGroup::setNewGroupMode()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(tr("Nouveau Groupe"));  // Ajouter "Nouveau Groupe" // Add "New Group"
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setEnabled(false);  // Désactiver la comboBox pour forcer la création / Disable the comboBox to enforce creation mode
}

// Charger les noms de groupes dans la comboBox / Load group names into the comboBox
void winGroup::loadGroupNames()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(tr("Nouveau Groupe..."), QVariant(-1));  // Option "Nouveau Groupe" avec ID spécial -1

    int currentFolderId = databaseManager::getCurrentFolderId();  // Obtenir l'ID du dossier courant / Retrieve current folder ID

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("SELECT id_group, name_group FROM group_account WHERE id_user = :id_user AND is_deleted = 0");
    query.bindValue(":id_user", currentFolderId);

    if (!query.exec()) {
        // Affichage de l'erreur si la requête échoue / Show error if query fails
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des groupes."));
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString groupName = query.value(1).toString();
        ui->comboBox->addItem(groupName, id);  // Ajouter le groupe avec son ID / Add group with its ID
    }
}

// Gérer le changement de sélection dans la comboBox / Handle comboBox selection change
void winGroup::onComboBoxSelectionChanged(int index)
{
    int groupId = ui->comboBox->itemData(index).toInt();  // Récupérer l'ID du groupe sélectionné / Retrieve selected group ID

    if (groupId == -1) {
        // Mode création pour "Nouveau Groupe..." / Creation mode for "New Group..."
        clearGroupFields();
        toggleEditMode(true);
    } else {
        // Mode édition pour un groupe existant / Edit mode for an existing group
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("SELECT name_group, description FROM group_account WHERE id_group = :id");
        query.bindValue(":id", groupId);

        if (query.exec() && query.next()) {
            ui->lineEditNameGroup->setText(query.value("name_group").toString());
            ui->textEditDescGroup->setPlainText(query.value("description").toString());
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger les informations du groupe sélectionné."));
        }
        toggleEditMode(false);
    }
}

// Basculer entre mode création et modification / Toggle between creation and modification mode
void winGroup::toggleEditMode(bool isNew)
{
    if (isNew) {
        // Mode création : "Ok" et "Supprimer" cachés / Creation mode: "Ok" and "Delete" hidden
        ui->pushBtnOK->setText(tr("Ok"));
        ui->pushBtnSupp->setVisible(false);
    } else {
        // Mode modification : "M.A.J." et "Supprimer" visibles / Modification mode: "Update" and "Delete" visible
        ui->pushBtnOK->setText(tr("M.A.J."));
        ui->pushBtnSupp->setVisible(true);
    }
}

// Effacer les champs du groupe / Clear group fields
void winGroup::clearGroupFields()
{
    ui->lineEditNameGroup->clear();
    ui->textEditDescGroup->clear();
}

// Gérer la création ou modification du groupe / Handle group creation or modification
void winGroup::handleGroupOperation()
{
    int currentFolderId = databaseManager::getCurrentFolderId();
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    if (ui->comboBox->currentIndex() == 0) {
        // Mode création / Creation mode
        query.prepare("INSERT INTO group_account (name_group, description, id_user) VALUES (:name, :description, :id_user)");
        query.bindValue(":id_user", currentFolderId);
    } else {
        // Mode modification / Edit mode
        int groupId = ui->comboBox->currentData().toInt();
        query.prepare("UPDATE group_account SET name_group = :name, description = :description WHERE id_group = :id AND id_user = :id_user");
        query.bindValue(":id", groupId);
        query.bindValue(":id_user", currentFolderId);
    }

    query.bindValue(":name", ui->lineEditNameGroup->text());
    query.bindValue(":description", ui->textEditDescGroup->toPlainText());

    // Exécution de la requête et gestion de l'erreur / Execute the query and handle error
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de sauvegarder le groupe."));
        return;
    }

    accept();  // Fermer la fenêtre après succès / Close the window after success
}

// Gérer la suppression du groupe / Handle group deletion
void winGroup::handleGroupDeletion()
{
    int groupId = ui->comboBox->currentData().toInt();

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("DELETE FROM group_account WHERE id_group = :id AND id_user = :id_user");
    query.bindValue(":id", groupId);
    query.bindValue(":id_user", databaseManager::getCurrentFolderId());

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le groupe."));
        return;
    }

    // Suppression en cascade des liens au groupe dans la table des comptes / Cascade removal of links to the group in the account table
    query.prepare("UPDATE account SET id_group = NULL WHERE id_group = :id");
    query.bindValue(":id", groupId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de dissocier les comptes du groupe."));
        return;
    }

    accept();  // Fermer la fenêtre après suppression réussie / Close the window after successful deletion
}

// Empêcher la fermeture de la fenêtre / Prevent the window from closing
void winGroup::closeEvent(QCloseEvent *event)
{
    event->ignore();  // Ignorer l'événement de fermeture / Ignore the close event
}

// Destructeur / Destructor
winGroup::~winGroup()
{
    delete ui;
}
