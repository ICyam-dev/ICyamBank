#ifndef WINACCOUNT_H
#define WINACCOUNT_H

#include <QDialog>
#include <QSqlQuery>           // Inclusion pour exécuter des requêtes SQL / Include to execute SQL queries
#include <QPushButton>         // Inclusion pour gérer les boutons / Include to manage buttons
#include <QComboBox>           // Inclusion pour gérer les ComboBox / Include to manage ComboBoxes
#include <QCloseEvent>         // Inclusion pour gérer l'événement de fermeture / Include to manage close event

namespace Ui {
class winAccount;
}

class winAccount : public QDialog
{
    Q_OBJECT

public:
    explicit winAccount(QWidget *parent = nullptr);  // Constructeur par défaut / Default constructor
    ~winAccount();  // Destructeur pour nettoyer les ressources / Destructor to clean up resources

    // Définir le mode de la fenêtre : Création, Modification ou les deux / Define window mode: Creation, Modification, or both
    void setWindowMode(bool isCreation);

protected:
    void closeEvent(QCloseEvent *event) override;  // Empêche la fermeture de la fenêtre avec les boutons de contrôle / Prevents closing with control buttons

private:
    Ui::winAccount *ui;  // Interface utilisateur / User interface

    // **Méthodes pour charger les données dans les ComboBox / Methods to load data into ComboBoxes**
    void loadComboBoxAccount();        // Charger les comptes dans la ComboBox / Load accounts into the ComboBox
    void loadComboBoxAccountBank();    // Charger les banques dans la ComboBox / Load banks into the ComboBox
    void loadComboBoxAccountDevise();  // Charger les devises dans la ComboBox / Load currencies into the ComboBox
    void loadComboBoxAccountType();    // Charger les types de comptes dans la ComboBox / Load account types into the ComboBox
    void loadComboBoxAccountGroup();   // Charger les groupes de comptes dans la ComboBox / Load account groups into the ComboBox

    void clearFields();                // Efface tous les champs pour un nouveau compte / Clears all fields for a new account
    void setEditMode(bool isEdit);     // Basculer entre les modes Création et Modification / Toggle between Creation and Edit modes

    // **Méthodes de sélection dans les ComboBox / ComboBox Selection Methods**
    void selectComboBoxItemById(QComboBox *comboBox, int id);  // Sélectionner un élément par ID dans une ComboBox / Select item by ID in ComboBox

    int currentAccountId = -1;  // ID du compte actuel pour les modifications / Current account ID for edits

private slots:
    void handleOkButtonClick();          // Gestion du clic du bouton OK / Handle OK button click
    void handleCancelButtonClick();      // Gestion du clic du bouton Annuler / Handle Cancel button click
    void handleDeleteButtonClick();      // Gestion du clic du bouton Supprimer / Handle Delete button click
    void handleAddBankButtonClick();     // Slot pour ajouter une banque / Slot to add a bank
    void handleAddGroupButtonClick();    // Slot pour ajouter un groupe / Slot to add a group

    void updateBankComboBoxAfterCreation();  // Mettre à jour la ComboBox Banque après création / Update Bank ComboBox after creation
    void updateGroupComboBoxAfterCreation(); // Mettre à jour la ComboBox Groupe après création / Update Group ComboBox after creation

    void onComboBoxAccountSelectionChanged(int index);  // Gérer la sélection d'un compte existant / Handle existing account selection
};

#endif // WINACCOUNT_H
