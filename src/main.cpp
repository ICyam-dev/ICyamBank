#include "header/mainwindow.h"
#include "header/objICyamApp.h"           // Inclusion de objICyamApp pour les méthodes centralisées / Inclusion of objICyamApp for centralized methods
#include "header/databaseManager.h"        // Inclusion de databaseManager pour insérer les données par défaut / Including databaseManager to insert default data

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // **Gestion des traductions / Handling translations**
    // Charger les traductions selon la langue du système / Load translations based on system language
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ICyamBank_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // **Initialisation de l'application / Application initialization**
    // Indiquer qu'aucun dossier n'est sélectionné au démarrage
    // Set selected folder to -1 to indicate no active folder on startup
    objICyamApp::setSelectedFolderId(-1);

    // **Initialisation de la base de données / Database initialization**
    // Configurer la base de données et insérer les données par défaut si besoin
    // Set up the database and insert default data if needed
    int initResult = objICyamApp::initDatabase("ICyamBank.db");

    if (initResult == -1) {
        // En cas d'échec de configuration de la base de données, afficher un message d'erreur et quitter
        // If database setup fails, display an error message and exit
        qDebug() << QObject::tr("Erreur : Échec de la configuration de la base de données.");
        return -1;  // Quitter si la configuration de la base échoue / Exit if database setup fails
    }
    else if (initResult == 1) {
        // **Insertion des données par défaut / Inserting default data**
        // Ajouter les types de comptes et l'utilisateur par défaut si la base est neuve
        // Add default account types and user if the database is new
        databaseManager::insertDefaultAccountTypes();
        databaseManager::insertDefaultUser();
    }
    else {
        // La base est déjà configurée, aucune autre action n'est nécessaire
        // The database is already configured, no further action needed
        qDebug() << QObject::tr("La base de données est déjà configurée.");
    }

    // **Création et affichage de la fenêtre principale / Creating and displaying the main window**
    // Afficher la fenêtre principale en plein écran pour une meilleure expérience
    // Display the main window in maximized mode for a better experience
    MainWindow w;
    w.showMaximized();

    // **Exécution de la boucle principale de l'application / Running the application's main event loop**
    return a.exec();  // Démarrer la boucle d'événements principale / Start the main event loop
}
