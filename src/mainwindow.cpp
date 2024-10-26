#include "header/mainwindow.h"
#include "header/winCurrentUser.h"
#include "ui_mainwindow.h"
#include "header/interfaceManager.h"  // Inclusion de la classe InterfaceManager / Including InterfaceManager class
#include "header/winAbout.h"          // Inclusion de la fenêtre WinAbout / Including WinAbout window
#include "header/winAccount.h"        // Inclusion de winAccount / Including winAccount
#include "header/winGroup.h"          // Inclusion de winGroup / Including winGroup
#include "header/winUser.h"           // Inclure winUser / Including winUser
#include "header/winBank.h"           // Inclure winBank / Including winBank
#include <QSqlDatabase>
#include <QDebug>
#include <QTimer>  // Inclure QTimer pour gérer le délai d'ouverture / Including QTimer to manage open delay

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Afficher les pilotes disponibles pour confirmation
    // Show available drivers for confirmation
    qDebug() << "Drivers disponibles:" << QSqlDatabase::drivers();

    // Créer un QSplitter pour diviser la zone de gauche et de droite
    // Create a QSplitter to divide the left and right areas
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    InterfaceManager* interfaceManager = new InterfaceManager(splitter, ui->comboBoxSortAcount, ui->treeWidgetAccount, this);
    ui->horizontalLayout->addWidget(splitter);

    // Ouvrir la fenêtre utilisateur après l'affichage de MainWindow
    // Open the user window after MainWindow display
    QTimer::singleShot(100, this, &MainWindow::openUserDialog);

    // Connexions explicites pour chaque action
    // Explicit connections for each action
    connect(ui->actionOpenCreateFolder, &QAction::triggered, this, &MainWindow::openCreateFolder);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
    connect(ui->actionBank, &QAction::triggered, this, &MainWindow::openBankWindow);
    connect(ui->actionAccount, &QAction::triggered, this, &MainWindow::openAccountWindow);
    connect(ui->actionGroup, &QAction::triggered, this, &MainWindow::openGroupWindow);
    connect(ui->actionCurrentUser, &QAction::triggered, this, &MainWindow::openCurrentUser);
}

// Méthode pour activer ou désactiver certaines actions (menu, boutons, etc.)
// Method to enable or disable certain actions (menu, buttons, etc.)
void MainWindow::updateActions(bool enabled)
{
    ui->actionBank->setEnabled(enabled);
    ui->actionAccount->setEnabled(enabled);
    ui->actionGroup->setEnabled(enabled);
    ui->actionCurrentUser->setEnabled(enabled);
}

// Ouverture automatique de la fenêtre utilisateur après affichage
// Automatic opening of the user window after display
void MainWindow::openUserDialog()
{
    winUser userDialog(this);
    userDialog.exec();  // Affiche la fenêtre utilisateur en mode modal / Show user window in modal mode
}

// Slot pour l'ouverture manuelle de la fenêtre winUser
// Slot for manually opening the winUser window
void MainWindow::openCreateFolder()
{
    winUser userDialog(this);
    userDialog.exec();
}

// Afficher la fenêtre "À propos" en mode modal
// Display the "About" window in modal mode
void MainWindow::showAbout()
{
    WinAbout aboutDialog(this);
    aboutDialog.setModal(true);
    aboutDialog.exec();
}

// Ouverture de la fenêtre bancaire en mode hybride
// Open the banking window in hybrid mode
void MainWindow::openBankWindow()
{
    winBank *bankWindow = new winBank(false, this);  // Mode hybride : création/modification/suppression / Hybrid mode: creation/modification/deletion
    bankWindow->exec();  // Affiche la fenêtre en mode modal / Display the window in modal mode
}

// Ouverture de la fenêtre de gestion des comptes
// Open the account management window
void MainWindow::openAccountWindow()
{
    winAccount *accountWindow = new winAccount(this);
    accountWindow->exec();
}

// Ouverture de la fenêtre de gestion des groupes
// Open the group management window
void MainWindow::openGroupWindow()
{
    // Création de la fenêtre winGroup en mode hybride (création/modification/suppression)
    // Create winGroup window in hybrid mode (creation/modification/deletion)
    winGroup *groupWindow = new winGroup(false, this);

    // Afficher la fenêtre en mode modal
    // Display the window in modal mode
    groupWindow->exec();

    // Nettoyer après fermeture de la fenêtre
    // Clean up after closing the window
    delete groupWindow;
}

// Ouverture de la fenêtre des informations utilisateur en cours
// Open the current user information window
void MainWindow::openCurrentUser()
{
    winCurrentUser currentUserDialog(this);
    currentUserDialog.exec();
}

// Destructeur / Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
