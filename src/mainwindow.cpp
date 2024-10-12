#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include "header/databaseManager.h"  // Inclusion du gestionnaire de base de données / Including the database manager
#include "header/leftcolumnmanager.h"  // Inclusion de la classe LeftColumnManager / Including the LeftColumnManager class
#include <QSplitter>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    // Ajouter les widgets gauche et droit au splitter
    // Add the left and right widgets to the splitter
    splitter->addWidget(ui->widgetLeft);
    splitter->addWidget(ui->widgetRight);

    // Définir la taille initiale des deux widgets dans le splitter (20% pour la gauche, 80% pour la droite)
    // Set the initial size of both widgets in the splitter (20% for left, 80% for right)
    QList<int> sizes;
    sizes << this->width() * 0.20 << this->width() * 0.80;  // Calcul des proportions / Calculating the proportions
    splitter->setSizes(sizes);

    // Limiter les dimensions lors du redimensionnement
    // Limit the dimensions during resizing
    connect(splitter, &QSplitter::splitterMoved, this, [=](int pos, int index) {
        int totalWidth = this->width();  // Largeur totale de la fenêtre / Total width of the window
        int minLeftWidth = totalWidth * 0.15;  // Limite de 15% pour la gauche / 15% limit for the left side
        int maxLeftWidth = totalWidth * 0.40;  // Limite de 40% pour la gauche / 40% limit for the left side

        // Vérifier et ajuster la largeur du widget gauche pour rester dans les limites
        // Check and adjust the width of the left widget to stay within the limits
        if (splitter->sizes().at(0) < minLeftWidth) {
            splitter->setSizes({minLeftWidth, totalWidth - minLeftWidth});
        } else if (splitter->sizes().at(0) > maxLeftWidth) {
            splitter->setSizes({maxLeftWidth, totalWidth - maxLeftWidth});
        }
    });

    // Ajouter le QSplitter dans le layout principal
    // Add the QSplitter to the main layout
    ui->horizontalLayout->addWidget(splitter);

    // Initialiser le gestionnaire de la colonne de gauche après l'initialisation complète de l'interface
    // Initialize the LeftColumnManager after the full initialization of the interface
    LeftColumnManager* leftColumnManager = new LeftColumnManager(ui->comboBoxSortAcount, ui->treeWidgetAccount, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
