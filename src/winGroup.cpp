#include "header/winGroup.h"
#include "ui_winGroup.h"
#include <QSqlQuery>       // Inclusion pour exécuter des requêtes SQL / Inclusion for executing SQL queries
#include <QSqlError>       // Inclusion pour capturer les erreurs SQL / Inclusion to capture SQL errors
#include <QMessageBox>     // Inclusion pour afficher des messages d'erreur / Inclusion to display error messages
#include <QDebug>          // Inclusion pour afficher des informations de débogage / Inclusion for debug information

winGroup::winGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winGroup)
{
    ui->setupUi(this);

    // Empêcher l'agrandissement et fixer la taille de la fenêtre
    // Prevent resizing and set the window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Mettre le bouton "Supprimer" en rouge et invisible par défaut
    // Set the "Delete" button in red and hide it by default
    QPalette palette = ui->pushBtnSupp->palette();
    palette.setColor(QPalette::ButtonText, Qt::red);
    ui->pushBtnSupp->setPalette(palette);
    ui->pushBtnSupp->setVisible(false);

    // Charger les noms de groupes dans la comboBox
    // Load group names into the comboBox
    loadGroupNames();

    // Connexion pour détecter le changement dans la comboBox
    // Connect to detect changes in the comboBox
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winGroup::onComboBoxSelectionChanged);

    // Connexion des boutons
    // Connect the buttons
    connect(ui->pushBtnOK, &QPushButton::clicked, this, &winGroup::handleGroupOperation);
    connect(ui->pushBtnSupp, &QPushButton::clicked, this, &winGroup::handleGroupDeletion);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// Méthode pour verrouiller la comboBox sur "Nouveau Groupe"
// Method to lock the comboBox on "New Group"
void winGroup::setNewGroupMode()
{
    ui->comboBox->setCurrentIndex(0);  // Sélectionner "Nouveau Groupe..." // Select "New Group..."
    ui->comboBox->setEnabled(false);   // Désactiver la comboBox pour forcer la création // Disable the comboBox to force creation mode
}

// Charger les noms de groupes dans la comboBox
// Load group names into the comboBox
void winGroup::loadGroupNames()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(tr("Nouveau Groupe"));  // Ajouter "Nouveau Groupe" // Add "New Group"

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (!query.exec("SELECT id_group, name_group FROM group_account")) {
        // Affichage du message d'erreur
        // Display the error message
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer la liste des groupes."));
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString groupName = query.value(1).toString();
        // Ajouter les groupes dans la comboBox
        // Add groups to the comboBox
        ui->comboBox->addItem(groupName, id);
    }
}

// Gérer le changement de sélection dans la comboBox
// Handle comboBox selection change
void winGroup::onComboBoxSelectionChanged(int index)
{
    if (index == 0) {
        // Mode création
        // Creation mode
        clearGroupFields();
        toggleEditMode(true);
    } else {
        // Mode édition
        // Edit mode
        int groupId = ui->comboBox->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("SELECT * FROM group_account WHERE id_group = :id");
        query.bindValue(":id", groupId);

        if (query.exec() && query.next()) {
            // Remplir les champs avec les données du groupe sélectionné
            // Fill the fields with the selected group's data
            ui->lineEditNameGroup->setText(query.value("name_group").toString());
            ui->textEditDescGroup->setPlainText(query.value("description_group").toString());
        }

        toggleEditMode(false);  // Passer en mode édition // Switch to edit mode
    }
}

// Basculer entre mode création et modification
// Toggle between creation and modification mode
void winGroup::toggleEditMode(bool isNew)
{
    if (isNew) {
        // Mode création : "Ok" et "Supprimer" caché
        // Creation mode: "Ok" and "Delete" hidden
        ui->pushBtnOK->setText(tr("Ok"));
        ui->pushBtnSupp->setVisible(false);
    } else {
        // Mode modification : "M.A.J." et "Supprimer" visible
        // Modification mode: "M.A.J." and "Delete" visible
        ui->pushBtnOK->setText(tr("M.A.J."));
        ui->pushBtnSupp->setVisible(true);
    }
}

// Vider les champs du groupe
// Clear the group's fields
void winGroup::clearGroupFields()
{
    ui->lineEditNameGroup->clear();
    ui->textEditDescGroup->clear();
}

// Gérer l'opération de création ou de modification du groupe
// Handle group creation or modification
void winGroup::handleGroupOperation()
{
    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    if (ui->comboBox->currentIndex() == 0) {
        // Mode création
        // Creation mode
        query.prepare("INSERT INTO group_account (name_group, description_group) VALUES (:name, :description)");
    } else {
        // Mode modification
        // Modification mode
        int groupId = ui->comboBox->currentData().toInt();
        query.prepare("UPDATE group_account SET name_group = :name, description_group = :description WHERE id_group = :id");
        query.bindValue(":id", groupId);
    }

    query.bindValue(":name", ui->lineEditNameGroup->text());
    query.bindValue(":description", ui->textEditDescGroup->toPlainText());

    if (!query.exec()) {
        // Affichage d'une erreur si la sauvegarde échoue
        // Display an error if saving fails
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de sauvegarder le groupe."));
        qDebug() << "Erreur SQL lors de la sauvegarde du groupe:" << query.lastError();
        return;
    }

    accept();  // Fermer la fenêtre après succès // Close the window after success
}

// Gérer la suppression du groupe
// Handle group deletion
void winGroup::handleGroupDeletion()
{
    int groupId = ui->comboBox->currentData().toInt();

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    query.prepare("DELETE FROM group_account WHERE id_group = :id");
    query.bindValue(":id", groupId);

    if (!query.exec()) {
        // Affichage d'une erreur si la suppression échoue
        // Display an error if deletion fails
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de supprimer le groupe."));
        qDebug() << "Erreur SQL lors de la suppression du groupe:" << query.lastError();
        return;
    }

    // Mettre à jour la table account en supprimant les liaisons au groupe supprimé
    // Update the account table by removing links to the deleted group
    query.prepare("UPDATE account SET id_group = NULL WHERE id_group = :id");
    query.bindValue(":id", groupId);

    if (!query.exec()) {
        // Affichage d'une erreur si la dissociation échoue
        // Display an error if dissociation fails
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de dissocier les comptes du groupe."));
        qDebug() << "Erreur SQL lors de la dissociation des comptes:" << query.lastError();
        return;
    }

    accept();  // Fermer la fenêtre après suppression // Close the window after deletion
}

void winGroup::closeEvent(QCloseEvent *event)
{
    // Empêcher la fermeture de la fenêtre
    // Prevent the window from being closed
    event->ignore();  // Ignorer l'événement de fermeture // Ignore the close event
}

winGroup::~winGroup()
{
    delete ui;
}
