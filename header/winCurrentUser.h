#ifndef WINCURRENTUSER_H
#define WINCURRENTUSER_H

#include <QDialog>

namespace Ui {
class winCurrentUser;
}

class winCurrentUser : public QDialog
{
    Q_OBJECT

public:
    explicit winCurrentUser(QWidget *parent = nullptr);
    ~winCurrentUser();  // Destructeur pour libérer les ressources / Destructor to release resources

private slots:
    void handleCancelButtonClick();  // Gérer le clic du bouton "Annuler" / Handle "Cancel" button click
    void handleOkButtonClick();      // Gérer le clic du bouton "Ok" / Handle "Ok" button click

private:
    Ui::winCurrentUser *ui;  // Interface utilisateur pour la fenêtre / User interface for the window

    // **Méthodes de configuration et de chargement / Configuration and Loading Methods**
    void configureWindow();          // Configurer les propriétés de la fenêtre / Configure window properties
    void loadCurrentUserData();      // Charger les données utilisateur dans les champs / Load user data into fields

    // **Méthode de mise à jour des données / Data Update Method**
    void updateUserData();           // Mettre à jour les informations utilisateur dans la base de données / Update user information in the database
};

#endif // WINCURRENTUSER_H
