#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Méthode pour activer ou désactiver certaines actions (menu, boutons, etc.)
    // Method to enable or disable certain actions (menu, buttons, etc.)
    void updateActions(bool enabled);

protected:
    // Méthode pour ouvrir la boîte de dialogue utilisateur
    // Method to open the user dialog
    void openUserDialog();

private slots:
    // Slots pour gérer l'ouverture des différentes fenêtres de l'application
    // Slots to handle opening various application windows
    void openCreateFolder();      // Ouvrir manuellement winUser / Manually open winUser
    void showAbout();             // Afficher la fenêtre À propos / Display the About window
    void openBankWindow();        // Ouvrir la fenêtre bancaire / Open the bank management window
    void openAccountWindow();     // Ouvrir la fenêtre de gestion des comptes / Open the account management window
    void openGroupWindow();       // Ouvrir la fenêtre de gestion des groupes / Open the group management window
    void openCurrentUser();       // Ouvrir winCurrentUser / Open winCurrentUser

private:
    Ui::MainWindow *ui;           // Interface utilisateur / User interface
};

#endif // MAINWINDOW_H
