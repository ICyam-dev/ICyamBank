#ifndef WINACCOUNT_H
#define WINACCOUNT_H

#include <QDialog>
#include <QCloseEvent>   // Inclusion pour gérer l'événement de fermeture / Inclusion to handle close event

namespace Ui {
class winAccount;
}

class winAccount : public QDialog
{
    Q_OBJECT

public:
    explicit winAccount(QWidget *parent = nullptr);
    ~winAccount();

protected:
    void closeEvent(QCloseEvent *event) override;  // Méthode pour empêcher la fermeture avec les boutons de contrôle / Method to prevent closing with control buttons

private:
    Ui::winAccount *ui;

    // Ajout des méthodes pour charger les ComboBox / Adding methods to load ComboBoxes
    void loadComboBoxAccount();        // Charger les comptes dans la ComboBox / Load accounts into the ComboBox
    void loadComboBoxAccountBank();    // Charger les banques dans la ComboBox / Load banks into the ComboBox
    void loadComboBoxAccountGroup();   // Charger les groupes dans la ComboBox / Load account groups into the ComboBox
    void updateDocumentList();         // Fonction pour mettre à jour la liste des documents / Function to update the document list
    void saveAccountData();            // Déclaration de la méthode / Declaration of the method

    QPushButton *pushBtnAddBank;   // Bouton pour ajouter une banque / Button to add a bank
    QPushButton *pushBtnAddGroup;  // Bouton pour ajouter un groupe / Button to add a group
    QPushButton *pushBtnAddDoc;    // Bouton pour ajouter un document / Button to add a document

    // Identifiant pour le compte courant (utilisé lors de l'ajout de documents, par exemple) / Current account ID
    int currentAccountId;   // Ajout de l'ID du compte actuel pour les opérations liées aux documents

private slots:
    void on_pushBtnCancel_clicked();   // Slot pour gérer le clic sur le bouton "Annuler" / Slot to handle the "Cancel" button click
    void on_pushBtnAddBank_clicked();  // Slot pour gérer le clic sur le bouton "Ajouter Banque" / Slot to handle the "Add Bank" button click
    void on_pushBtnAddGroup_clicked(); // Slot pour gérer le clic sur le bouton "Ajouter Groupe" / Slot to handle the "Add Group" button click
    void on_pushBtnAddDoc_clicked();   // Slot pour gérer l'ajout de document / Slot to handle document addition
    void on_pushBtnOk_clicked();       // Slot pour gérer l'enregistrement d'un compte / Slot to handle account saving
    void on_pushBtnSupp_clicked();     // Slot pour gérer la suppression logique d'un compte / Slot to handle soft delete of an account
};

#endif // WINACCOUNT_H
