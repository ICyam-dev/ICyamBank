#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "ui_mainwindow.h"
#include "mainWindowUpdate.h"  // Inclusion de mainWindowUpdate / Including mainWindowUpdate

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

    // Accesseur pour l'objet MainWindowUpdate / Getter for the MainWindowUpdate object
    MainWindowUpdate* getMainWindowUpdater();

    // Accesseur pour le comboBox de tri des comptes
    // Getter for the account sorting comboBox
    QComboBox* getComboBoxSortAccount() const;

    // Renvoie un pointeur vers le label du solde du dossier
    // Returns a pointer to the folder balance label
    QLabel* getLabelBalanceFolder() const { return ui->labelBalanceFolder; }

private slots:
    // Slots pour gérer l'ouverture des différentes fenêtres de l'application
    // Slots to handle opening various application windows
    void openCreateFolder();    // Ouvre la fenêtre pour créer un dossier / Opens the folder creation window
    void showAbout();           // Ouvre la fenêtre "À propos" / Opens the "About" window
    void openBankWindow();      // Ouvre la fenêtre de gestion bancaire / Opens the bank management window
    void openAccountWindow();   // Ouvre la fenêtre de gestion des comptes / Opens the account management window
    void openGroupWindow();     // Ouvre la fenêtre de gestion des groupes / Opens the group management window
    void openCurrentUser();     // Ouvre la fenêtre des informations de l'utilisateur courant / Opens the current user information window
    void openUserDialog();      // Ajout de la déclaration de openUserDialog / Declaration for openUserDialog
    void onTreeViewItemClicked(QTreeWidgetItem *item, int column);  // Slot pour gérer le clic sur un élément / Slot to handle item click
    void showContextMenu(const QPoint &pos);  // Slot pour afficher le menu contextuel / Slot to display the context menu


private:
    Ui::MainWindow *ui;           // Interface utilisateur / User interface
    MainWindowUpdate m_updater;   // Objet MainWindowUpdate intégré / Embedded MainWindowUpdate object

    // Méthode pour rafraîchir l'interface
    // Method to refresh the interface
    void refreshInterface();

    // Calculer le solde total d'un dossier donné
    // Calculate the total balance of a given folder
    double calculateFolderBalance(int folderID);

    void initializeContextMenuTreeView();  // Méthode pour initialiser le menu contextuel / Method to initialize the context menu

    // Déclaration des actions du menu contextuel / Declaration of context menu actions
    QAction *m_actionNewBank;
    QAction *m_actionEditBank;
    QAction *m_actionDeleteBank;
    QAction *m_actionNewGroup;
    QAction *m_actionEditGroup;
    QAction *m_actionDeleteGroup;
    QAction *m_actionNewAccount;
    QAction *m_actionEditAccount;
    QAction *m_actionDeleteAccount;

};

#endif // MAINWINDOW_H
