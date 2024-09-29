#include "header/mainwindow.h"
#include "header/databaseManager.h"  // Inclusion du gestionnaire de base de données // Including the database manager

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Gestion des traductions
    // Handling translations
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ICyamBank_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Vérification de la base de données
    // Database verification
    if (!databaseManager::setupDatabase()) {
        qDebug() << QObject::tr("Erreur : Échec de la configuration de la base de données.");  // Error: Database setup failed
        return -1;  // Sortir si la base de données ne peut pas être configurée // Exit if the database cannot be set up
    }

    // Création et affichage de la fenêtre principale en mode maximisé
    // Creating and showing the main window in maximized mode
    MainWindow w;
    w.showMaximized();  // Ouvrir la fenêtre en mode maximisé // Open the window in maximized mode

    return a.exec();  // Exécution de la boucle principale de l'application // Running the application's main event loop
}
