#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include "header/databaseManager.h"  // Inclusion du gestionnaire de base de données / Including the database manager
#include "header/interfaceManager.h"  // Inclusion de la classe InterfaceManager / Including the InterfaceManager class
#include "header/winabout.h"  // Inclusion de la fenêtre WinAbout / Including the WinAbout window
#include "header/winAccount.h"  // Inclusion du fichier d'en-tête pour winAccount / Include header for winAccount
#include "header/winGroup.h"  // Inclusion pour winGroup
#include <QSqlDatabase>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Afficher les pilotes disponibles / Display available SQL drivers
    qDebug() << "Drivers disponibles:" << QSqlDatabase::drivers();

    // Vérifier si la base de données est prête et afficher le chemin dans la barre de statut
    // Check if the database is ready and display the path in the status bar
    QString dbPath = databaseManager::getDatabasePath();  // Récupérer le chemin de la base de données / Get the database path

    if (databaseManager::setupDatabase()) {
        // Afficher le chemin d'accès à gauche de la barre de statut avec traduction
        // Display the database path on the left of the status bar with translation
        statusBar()->showMessage(tr("Base de données: ") + dbPath);
    } else {
        // Afficher un message d'erreur si la base de données ne peut pas être connectée
        // Show an error message if the database cannot be connected
        statusBar()->showMessage(tr("Échec de la connexion à la base de données"), 5000);
    }

    // Créer un QSplitter pour diviser la zone de gauche et de droite
    // Create a QSplitter to divide the left and right areas
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    // Initialiser InterfaceManager pour gérer le splitter et la colonne gauche
    // Initialize InterfaceManager to manage the splitter and the left column
    InterfaceManager* interfaceManager = new InterfaceManager(splitter, ui->comboBoxSortAcount, ui->treeWidgetAccount, this);

    // Ajouter le QSplitter dans le layout principal
    // Add the QSplitter to the main layout
    ui->horizontalLayout->addWidget(splitter);
}

// Slot pour gérer l'ouverture de la fenêtre "À propos" / Slot to handle the opening of the "About" window
void MainWindow::on_actionAbout_triggered()
{
    // Créer et afficher la fenêtre WinAbout / Create and show the WinAbout window
    WinAbout aboutDialog(this);
    aboutDialog.setModal(true);  // Rendre la fenêtre modale / Make the window modal
    aboutDialog.exec();  // Ouvrir la fenêtre en mode dialogue / Open the window as a dialog
}

void MainWindow::on_actionBank_triggered()
{
    // Créer une nouvelle fenêtre pour gérer les informations bancaires
    winBank *bankWindow = new winBank(this);  // Créer une instance de la fenêtre

    // Ajout d'un filtre pour n'afficher que les banques actives
    // The winBank window already filters for active banks using is_active = 1
    bankWindow->exec();  // Ouvrir la fenêtre en mode modal
}

void MainWindow::on_actionAccount_triggered()
{
    // Créer et afficher la fenêtre winAccount / Create and display winAccount window
    winAccount *accountWindow = new winAccount(this);
    accountWindow->exec();  // Ouvrir la fenêtre en mode modal / Open the window in modal mode
}

void MainWindow::on_actionGroup_triggered()
{
    // Ouvrir la fenêtre winGroup en mode Création/Modification
    winGroup groupDialog(this);  // Création de l'instance de winGroup
    groupDialog.setWindowModality(Qt::ApplicationModal);  // Ouvrir la fenêtre en mode modal

    if (groupDialog.exec() == QDialog::Accepted) {
        // Logique supplémentaire après la fermeture de la fenêtre, si nécessaire
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
