#ifndef WINUSER_H
#define WINUSER_H

#include <QDialog>
#include "header/databaseManager.h"  // Inclusion de databaseManager pour gérer les interactions avec la BDD / Including databaseManager to manage interactions with the database

namespace Ui {
class winUser;
}

class winUser : public QDialog
{
    Q_OBJECT

public:
    explicit winUser(QWidget *parent = nullptr);
    ~winUser();

private:
    Ui::winUser *ui;
    databaseManager dbManager;  // Instance de databaseManager pour gérer la base de données / Instance of databaseManager to handle database interactions

    // Méthode pour configurer la fenêtre
    // Method to configure the window
    void configureWindow();

    // Charger les dossiers dans la comboBox
    // Load folders into the comboBox
    void loadComboBoxFolder();

    // Méthode pour activer/désactiver les actions dans MainWindow
    // Method to enable/disable actions in MainWindow
    void updateMainWindowStatus(bool enabled);

    // Mise à jour de la barre de statut dans MainWindow
    // Update the status bar in MainWindow
    void updateMainWindowStatusBar();

    int selectedFolderId = -1;  // Stocker l'ID du dossier sélectionné
        // Store the ID of the selected folder

private slots:
    // Gérer le clic sur le bouton Annuler
    // Handle the Cancel button click
    void handleCancelClick();

    // Gérer le clic sur le bouton OK
    // Handle the OK button click
    void handleOkClick();

    // Gérer le changement de sélection dans la comboBox de dossiers
    // Handle folder comboBox selection change
    void handleFolderComboBoxChange(int index);

protected:
    // Empêcher la fermeture de la fenêtre avec le bouton de fermeture
    // Prevent closing the window with the close button
    void closeEvent(QCloseEvent *event) override;
};

#endif // WINUSER_H
