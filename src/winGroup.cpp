#include "header/databaseManager.h"  // Inclusion pour accéder à currentFolderId() / Include to access currentFolderId()
#include "header/winGroup.h"
#include "header/objICyamApp.h"
#include "ui_winGroup.h"
#include <QSqlQuery>       // Inclusion pour exécuter des requêtes SQL / Include to execute SQL queries
#include <QSqlError>       // Inclusion pour capturer les erreurs SQL / Include to capture SQL errors
#include <QMessageBox>     // Inclusion pour afficher des messages d'erreur / Include to display error messages

// Constructeur modifié pour accepter le paramètre "isCreationMode" / Modified constructor to accept "isCreationMode" parameter
winGroup::winGroup(bool isCreationMode, QWidget *parent) : QDialog(parent), ui(new Ui::winGroup)
{
    ui->setupUi(this);

    // Empêcher l'agrandissement et fixer la taille de la fenêtre / Prevent resizing and set fixed window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Configurer le bouton "Supprimer" en rouge et invisible par défaut / Set "Delete" button to red and invisible by default
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

    // Connexion des signaux pour détecter les changements et les actions des boutons / Connect signals to detect changes and button actions
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winGroup::onComboBoxSelectionChanged);
    connect(ui->pushBtnOK, &QPushButton::clicked, this, &winGroup::handleGroupOperation);
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winGroup::handleGroupDeletion);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// Basculer la comboBox sur "Nouveau Groupe" et verrouiller la sélection / Switch comboBox to "New Group" and lock selection
void winGroup::setNewGroupMode()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(tr("Nouveau Groupe"));  // Ajouter "Nouveau Groupe" / Add "New Group"
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setEnabled(false);  // Désactiver la comboBox pour forcer la création / Disable comboBox to force creation
}

// Charger les noms de groupes dans la comboBox pour le dossier en cours / Load group names into comboBox for the current folder
void winGroup::loadGroupNames()
{
    ui->comboBox->clear();  // Effacer la comboBox avant de la remplir / Clear comboBox before filling it
    ui->comboBox->addItem(tr("Nouveau Groupe..."), QVariant(-1));  // Option pour créer un nouveau groupe / Option to create a new group

    int currentFolderId = objICyamApp::getSelectedFolderId();  // Obtenir l'ID du dossier courant / Get current folder ID

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("SELECT id_group, name_group FROM group_account WHERE id_folder = :id_folder AND is_deleted = 0");
    query.bindValue(":id_folder", currentFolderId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des groupes."));
        qDebug() << "Erreur lors de l'exécution de la requête SQL pour les groupes:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString groupName = query.value(1).toString();
        ui->comboBox->addItem(groupName, id);  // Ajouter chaque groupe / Add each group
    }
}

// Gérer le changement de sélection dans la comboBox / Handle selection change in comboBox
void winGroup::onComboBoxSelectionChanged(int index)
{
    int groupId = ui->comboBox->itemData(index).toInt();  // Récupérer l'ID du groupe sélectionné / Retrieve selected group ID

    if (groupId == -1) {
        // Mode création pour "Nouveau Groupe..." / Creation mode for "New Group..."
        clearGroupFields();
        toggleEditMode(true);
    } else {
        // Mode édition pour un groupe existant / Edit mode for an existing group
        QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
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

// Basculer entre mode création et modification / Toggle between creation and edit mode
void winGroup::toggleEditMode(bool isNew)
{
    if (isNew) {
        // Mode création : "Ok" et "Supprimer" cachés / Creation mode: "OK" and "Delete" hidden
        ui->pushBtnOK->setText(tr("Ok"));
        ui->pushBtnSupp->setVisible(false);
    } else {
        // Mode modification : "M.A.J." et "Supprimer" visibles / Edit mode: "Update" and "Delete" visible
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
    int currentFolderId = objICyamApp::getSelectedFolderId();
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));

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

    // Exécution de la requête et gestion de l'erreur / Execute query and handle error
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de sauvegarder le groupe."));
        return;
    }

    accept();  // Fermer la fenêtre après succès / Close window after success
}

// Gérer la suppression du groupe / Handle group deletion
void winGroup::handleGroupDeletion()
{
    int groupId = ui->comboBox->currentData().toInt();

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare("DELETE FROM group_account WHERE id_group = :id AND id_user = :id_user");
    query.bindValue(":id", groupId);
    query.bindValue(":id_user", objICyamApp::getSelectedFolderId());

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le groupe."));
        return;
    }

    // Suppression en cascade des liens au groupe dans la table des comptes / Cascade deletion of group links in account table
    query.prepare("UPDATE account SET id_group = NULL WHERE id_group = :id");
    query.bindValue(":id", groupId);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de dissocier les comptes du groupe."));
        return;
    }

    accept();  // Fermer la fenêtre après suppression réussie / Close window after successful deletion
}

// Empêcher la fermeture de la fenêtre / Prevent window from closing
void winGroup::closeEvent(QCloseEvent *event)
{
    event->ignore();  // Ignorer l'événement de fermeture / Ignore close event
}

// Destructeur / Destructor
winGroup::~winGroup()
{
    delete ui;
}
