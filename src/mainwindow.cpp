#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include "header/databaseManager.h"  // Inclusion du gestionnaire de base de données // Including the database manager

#include <QLabel>
#include <QTranslator>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Vérifier si la base de données est prête et afficher le chemin dans la barre de statut
    // Check if the database is ready and display the path in the status bar
    QString dbPath = databaseManager::getDatabasePath();  // Récupérer le chemin de la base de données // Get the database path

    if (databaseManager::setupDatabase()) {
        // Afficher le chemin d'accès à gauche de la barre de statut avec traduction
        // Display the database path on the left of the status bar with translation
        statusBar()->showMessage(tr("Base de données: ") + dbPath);
    } else {
        statusBar()->showMessage(tr("Échec de la connexion à la base de données"), 5000);  // Afficher un message d'erreur // Show an error message
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
