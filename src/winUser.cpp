#include "header/winUser.h"
#include "header/mainwindow.h"
#include "ui_winUser.h"
#include <QStatusBar>
#include <QCloseEvent>
#include <QSqlQuery>          // Pour exécuter des requêtes SQL / To execute SQL queries
#include <QSqlError>          // Pour gérer les erreurs SQL / To handle SQL errors
#include <QMessageBox>        // Pour afficher des messages d'erreur / To display error messages
#include "header/databaseManager.h"  // Inclusion directe de databaseManager

// Constructeur / Constructor
winUser::winUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winUser)
{
    ui->setupUi(this);

    configureWindow();      // Configurer la fenêtre au démarrage / Configure the window at startup
    loadComboBoxFolder();   // Charger les dossiers dans la comboBox / Load folders into the comboBox

    // Connecter la comboBox et les boutons aux slots correspondants / Connect comboBox and buttons to the appropriate slots
    connect(ui->comboBoxFolder, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &winUser::on_comboBoxFolder_currentIndexChanged);
    connect(ui->pushBtnCancel, &QPushButton::clicked, this, &winUser::on_pushBtnCancel_clicked);
    connect(ui->pushBtnOk, &QPushButton::clicked, this, &winUser::on_pushBtnOk_clicked);
}

// Méthode pour configurer la fenêtre / Method to configure the window
void winUser::configureWindow()
{
    // Empêcher l'agrandissement et fixer la taille de la fenêtre / Prevent resizing and fix the window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Désactiver les boutons agrandir, rétrécir et fermer / Disable maximize, minimize, and close buttons
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);

    // Par défaut, activer les champs pour le mode "Création" / Enable fields for "Creation" mode by default
    ui->lineEditNameFolder->setEnabled(true);
    ui->textEditDescFolder->setEnabled(true);
}

// Charger les dossiers dans la comboBox / Load folders into the comboBox
void winUser::loadComboBoxFolder()
{
    ui->comboBoxFolder->clear();  // Vider la comboBox / Clear the comboBox
    ui->comboBoxFolder->addItem(tr("Nouveau Dossier..."));  // Ajouter l'option de création / Add the creation option

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
    if (query.exec("SELECT id_user, folder_name FROM user WHERE is_deleted = 0")) {
        while (query.next()) {
            int folderId = query.value(0).toInt();
            QString folderName = query.value(1).toString();
            ui->comboBoxFolder->addItem(folderName, folderId);  // Ajouter les dossiers existants / Add existing folders
        }
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Erreur lors du chargement des dossiers."));
    }
}

// Gérer le changement de sélection dans la comboBox / Handle comboBox selection change
void winUser::on_comboBoxFolder_currentIndexChanged(int index)
{
    if (index == 0) {  // Si "Nouveau Dossier..." est sélectionné / If "New Folder..." is selected
        ui->lineEditNameFolder->setEnabled(true);
        ui->textEditDescFolder->setEnabled(true);

        // Effacer les champs pour permettre la création d'un nouveau dossier / Clear fields for new folder creation
        ui->lineEditNameFolder->clear();
        ui->textEditDescFolder->clear();
    } else {
        // Charger les informations du dossier sélectionné / Load the selected folder's information
        int folderId = ui->comboBoxFolder->currentData().toInt();
        QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));
        query.prepare("SELECT folder_name, folder_desc FROM user WHERE id_user = :id_user AND is_deleted = 0");
        query.bindValue(":id_user", folderId);

        if (query.exec() && query.next()) {
            QString folderName = query.value(0).toString();
            QString folderDesc = query.value(1).toString();

            // Désactiver les champs et afficher les informations du dossier sélectionné / Disable fields and display folder information
            ui->lineEditNameFolder->setEnabled(false);
            ui->textEditDescFolder->setEnabled(false);
            ui->lineEditNameFolder->setText(folderName);
            ui->textEditDescFolder->setText(folderDesc);
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Erreur lors du chargement des informations du dossier."));
        }
    }
}

// Gérer le bouton "Annuler" / Handle the "Cancel" button
void winUser::on_pushBtnCancel_clicked()
{
    // Mise à jour de l'état des actions dans MainWindow si existant / Update actions state in MainWindow if present
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        mainWindow->updateActions(false);
    }
    this->reject();  // Fermer la fenêtre sans enregistrer / Close the window without saving
}

// Gérer le bouton "Ok" pour créer ou sélectionner un dossier / Handle "Ok" button to create or select a folder
void winUser::on_pushBtnOk_clicked()
{
    QString folderName = ui->lineEditNameFolder->text();
    QString folderDesc = ui->textEditDescFolder->toPlainText();

    // Vérification que le nom du dossier n'est pas vide / Check that the folder name is not empty
    if (folderName.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom du dossier ne peut pas être vide."));
        return;
    }

    QSqlQuery query(QSqlDatabase::database("ICyamBankConnection"));

    // Si "Nouveau Dossier..." est sélectionné, insérer un nouveau dossier / If "New Folder..." is selected, insert a new folder
    if (ui->comboBoxFolder->currentIndex() == 0) {
        query.prepare("INSERT INTO user (folder_name, folder_desc) VALUES (:folder_name, :folder_desc)");
        query.bindValue(":folder_name", folderName);
        query.bindValue(":folder_desc", folderDesc);

        if (!query.exec()) {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible de créer un nouveau dossier : %1").arg(query.lastError().text()));
            return;
        }

        // Récupérer l'ID du nouveau dossier inséré / Get the ID of the newly inserted folder
        selectedFolderId = query.lastInsertId().toInt();

    } else {
        // Si un dossier existant est sélectionné, récupérer son ID / If an existing folder is selected, get its ID
        selectedFolderId = ui->comboBoxFolder->currentData().toInt();
    }

    // Mettre à jour l'index du dossier dans databaseManager / Update folder index in databaseManager
    databaseManager::setCurrentFolderId(selectedFolderId);

    // Mise à jour des actions et de la barre de statut dans MainWindow / Update actions and status bar in MainWindow
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        mainWindow->updateActions(true);     // Activer les actions dans MainWindow / Enable actions in MainWindow
        updateMainWindowStatusBar();         // Mettre à jour la barre de statut / Update status bar
    }

    this->accept();  // Fermer la fenêtre après enregistrement / Close the window after saving
}

// Mettre à jour la barre de statut dans MainWindow / Update status bar in MainWindow
void winUser::updateMainWindowStatusBar()
{
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        QString dbPath = databaseManager::getDatabasePath();  // Obtenir le chemin de la base de données / Get the database path
        QString folderName = ui->lineEditNameFolder->text();

        mainWindow->statusBar()->showMessage(QString("📂 | %1 | %2 | %3 %4")
                                                 .arg(selectedFolderId)
                                                 .arg(folderName)
                                                 .arg(tr("Base de données :"))
                                                 .arg(dbPath));
    }
}

// Interdire la fermeture de la fenêtre avec le bouton de fermeture / Prevent closing the window with the close button
void winUser::closeEvent(QCloseEvent *event)
{
    event->ignore();  // Ignorer l'événement de fermeture / Ignore the close event
}

// Destructeur / Destructor
winUser::~winUser()
{
    delete ui;
}
