#ifndef WINBANK_H
#define WINBANK_H

#include <QDialog>
#include <QCloseEvent>   // Inclusion pour gérer l'événement de fermeture / Inclusion to handle close event
#include <QSqlError>     // Inclusion pour capturer les erreurs SQL / Inclusion to capture SQL errors

namespace Ui {
class winBank;
}

class winBank : public QDialog
{
    Q_OBJECT

public:
    // Constructeur modifié pour accepter un paramètre "isCreationMode"
    // Modified constructor to accept a "isCreationMode" parameter
    explicit winBank(bool isCreationMode, QWidget *parent = nullptr);
    ~winBank();

    // Méthode pour verrouiller la comboBox en mode "Nouvelle banque"
    // Method to lock the comboBox in "New Bank" mode
    void setNewBankMode();  // Méthode pour forcer le mode "Nouvelle banque" / Method to force "New Bank" mode

protected:
    void closeEvent(QCloseEvent *event) override;  // Ajout de la méthode closeEvent dans la déclaration / Addition of the closeEvent method in the declaration

private:
    Ui::winBank *ui;

    void loadBankNames(); // Charger les noms de banques dans la comboBox / Load bank names into the comboBox
    void toggleEditMode(bool isNew); // Basculer entre mode création et modification / Toggle between creation and edit mode
    void clearBankFields(); // Méthode pour vider les champs de la banque / Method to clear bank fields

private slots:
    void onComboBoxSelectionChanged(int index); // Méthode pour gérer le changement de sélection dans la comboBox / Method to handle comboBox selection change
    void handleBankOperation(); // Gérer l'opération de création ou de modification de la banque / Handle bank creation or modification operation
    void handleBankDeletion(); // Gérer la suppression d'une banque / Handle bank deletion
};

#endif // WINBANK_H
