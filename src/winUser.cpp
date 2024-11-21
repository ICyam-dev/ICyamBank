#include "header/winUser.h"
#include "header/objICyamApp.h"
#include "header/databaseManager.h"  // Inclusion directe de databaseManager / Direct inclusion of databaseManager
#include "header/mainWindowUpdate.h"  // Inclusion de mainWindowUpdate pour la mise à jour de l'interface / Inclusion of mainWindowUpdate for interface updates
#include "header/mainwindow.h"
#include "header/winInsertData.h"
#include "ui_winUser.h"
#include <QStatusBar>
#include <QCloseEvent>
#include <QSqlQuery>          // Pour exécuter des requêtes SQL / To execute SQL queries
#include <QSqlError>          // Pour gérer les erreurs SQL / To handle SQL errors
#include <QMessageBox>        // Pour afficher des messages d'erreur / To display error messages


// Constructeur / Constructor
winUser::winUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winUser)
{
    ui->setupUi(this);

    configureWindow();      // Configurer la fenêtre au démarrage / Configure the window at startup
    loadComboBoxFolder();   // Charger les dossiers dans la comboBox / Load folders into the comboBox

    // Connecter la comboBox et les boutons aux slots correspondants / Connect the comboBox and buttons to the appropriate slots
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &winUser::handleCancelClick);
    connect(ui->pushBtnOk, &QPushButton::clicked, this, &winUser::handleOkClick);
    connect(ui->comboBoxFolder, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winUser::handleFolderComboBoxChange);
}

// Méthode pour configurer la fenêtre / Method to configure the window
void winUser::configureWindow()
{
    // Empêcher l'agrandissement et fixer la taille de la fenêtre / Prevent resizing and set a fixed window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Désactiver les boutons agrandir, rétrécir et fermer / Disable maximize, minimize, and close buttons
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);

    // Par défaut, activer les champs pour le mode "Création" / By default, enable fields for "Create" mode
    ui->lineEditNameFolder->setEnabled(true);
    ui->textEditDescFolder->setEnabled(true);
}

// Charger les dossiers dans la comboBox / Load folders into the comboBox
void winUser::loadComboBoxFolder()
{
    ui->comboBoxFolder->clear();  // Vider la comboBox / Clear the comboBox
    ui->comboBoxFolder->addItem(tr("Nouveau Dossier..."));  // Ajouter l'option de création / Add creation option

    // Récupération et vérification de la connexion de la base de données / Retrieve and verify database connection
    QSqlDatabase db = QSqlDatabase::database("ICyamConnection");
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Erreur"), tr("La connexion à la base de données n'est pas ouverte."));
        qDebug() << "Connexion ICyamConnection n'est pas ouverte." << db.lastError().text();
        return;
    } else {
        qDebug() << "Connexion ICyamConnection est ouverte." << db.connectionName();
    }

    // Exécution de la requête SQL pour charger les dossiers / Execute SQL query to load folders
    QSqlQuery query(db);
    if (query.exec("SELECT id_user, folder_name FROM user WHERE is_deleted = 0")) {
        while (query.next()) {
            int folderId = query.value(0).toInt();
            QString folderName = query.value(1).toString();
            ui->comboBoxFolder->addItem(folderName, folderId);  // Ajouter chaque dossier / Add each folder
        }
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Erreur lors du chargement des dossiers."));
        qDebug() << "Échec de la requête SQL:" << query.lastError().text();
    }
}

// Gérer le changement de sélection dans la comboBox / Handle selection change in the comboBox
void winUser::handleFolderComboBoxChange(int index)
{
    if (index == 0) {  // Si "Nouveau Dossier..." est sélectionné / If "New Folder..." is selected
        ui->lineEditNameFolder->setEnabled(true);
        ui->textEditDescFolder->setEnabled(true);
        ui->lineEditNameFolder->clear();
        ui->textEditDescFolder->clear();
    } else {
        int folderId = ui->comboBoxFolder->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
        query.prepare("SELECT folder_name, folder_desc FROM user WHERE id_user = :id_user AND is_deleted = 0");
        query.bindValue(":id_user", folderId);

        if (query.exec() && query.next()) {
            QString folderName = query.value(0).toString();
            QString folderDesc = query.value(1).toString();

            ui->lineEditNameFolder->setEnabled(false);  // Désactiver le champ de nom / Disable the name field
            ui->textEditDescFolder->setEnabled(false);  // Désactiver le champ de description / Disable the description field
            ui->lineEditNameFolder->setText(folderName);  // Charger le nom du dossier / Load the folder name
            ui->textEditDescFolder->setText(folderDesc);  // Charger la description du dossier / Load the folder description
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Erreur lors du chargement des informations du dossier."));
        }
    }
}

// Gérer le bouton "Annuler" / Handle "Cancel" button
void winUser::handleCancelClick()
{
    //int folderID = objICyamApp::getSelectedFolderId();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        mainWindow->updateActions(false);  // Désactiver les actions dans la fenêtre principale / Disable actions in the main window
    }
    this->reject();  // Fermer la fenêtre sans enregistrer / Close the window without saving
}

// Gérer le bouton "OK" / Handle "OK" button
void winUser::handleOkClick()
{
    QString folderName = ui->lineEditNameFolder->text();
    QString folderDesc = ui->textEditDescFolder->toPlainText();

    if (folderName.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom du dossier ne peut pas être vide."));
        return;
    }

    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    int folderID;

    // Si "Nouveau Dossier..." est sélectionné, insérer un nouveau dossier / If "New Folder..." is selected, insert a new folder
    if (ui->comboBoxFolder->currentIndex() == 0) {
        query.prepare("INSERT INTO user (folder_name, folder_desc) VALUES (:folder_name, :folder_desc)");
        query.bindValue(":folder_name", folderName);
        query.bindValue(":folder_desc", folderDesc);

        if (!query.exec()) {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible de créer un nouveau dossier : %1").arg(query.lastError().text()));
            return;
        }

        folderID = query.lastInsertId().toInt();
        objICyamApp::setSelectedFolderId(folderID);  // Mettre à jour l'ID du dossier sélectionné / Update selected folder ID

        // Affichage de la fenêtre winInsertData à la place de la boîte de dialogue Oui/Non / Display winInsertData window instead of Yes/No dialog
        winInsertData insertDataDialog(this);
        insertDataDialog.setModal(true);
        insertDataDialog.exec();  // Cela affichera la fenêtre en mode bloquant (modal) / Displays the window in modal blocking mode

    } else {
        // Sinon, récupérer l'ID du dossier existant sélectionné / Otherwise, retrieve selected existing folder ID
        folderID = ui->comboBoxFolder->currentData().toInt();
    }

    // Mise à jour de l'ID du dossier sélectionné dans l'application / Update selected folder ID in the application
    objICyamApp::setSelectedFolderId(folderID);

    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        mainWindow->updateActions(true);  // Activer les actions dans la fenêtre principale / Enable actions in the main window
        //mainWindow->getMainWindowUpdater()->updateStatusBar(folderID);  // Mettre à jour la barre de statut / Update the status bar

        // Mise à jour de la comboBox pour le dossier sélectionné / Update the comboBox for the selected folder
        mainWindow->getMainWindowUpdater()->updateComboBoxOptions(mainWindow->getComboBoxSortAccount());
    }

    this->accept();  // Fermer la fenêtre après enregistrement / Close the window after saving
}

// Empêcher la fermeture de la fenêtre avec le bouton de fermeture / Prevent closing the window with the close button
void winUser::closeEvent(QCloseEvent *event)
{
    event->ignore();  // Ignorer l'événement de fermeture / Ignore the close event
}

// Destructeur / Destructor
winUser::~winUser()
{
    delete ui;
}
