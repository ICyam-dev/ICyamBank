#ifndef WINUSER_H
#define WINUSER_H

#include <QDialog>
#include "header/databaseManager.h"  // Inclusion de databaseManager pour gérer les interactions avec la BDD

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
    databaseManager dbManager;  // Instance de databaseManager pour gérer la base de données

    // Méthode pour configurer la fenêtre
    void configureWindow();
    // Charger les dossiers dans la comboBox
    void loadComboBoxFolder();
    // Méthode pour activer/désactiver les actions dans MainWindow
    void updateMainWindowStatus(bool enabled);
    // Mise à jour de la barre de statut dans MainWindow
    void updateMainWindowStatusBar();

    int selectedFolderId = -1;  // Stocker l'ID du dossier sélectionné

private slots:
    void on_pushBtnCancel_clicked();
    void on_pushBtnOk_clicked();
    void on_comboBoxFolder_currentIndexChanged(int index);

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // WINUSER_H
