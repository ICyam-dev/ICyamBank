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

    ~winBank();  // Destructeur pour libérer les ressources / Destructor to release resources

    // Forcer le mode "Nouvelle banque" en verrouillant la comboBox
    // Force "New Bank" mode by locking the comboBox
    void setNewBankMode();

protected:
    void closeEvent(QCloseEvent *event) override;  // Empêcher la fermeture avec les boutons de contrôle / Prevent closing with control buttons

private:
    Ui::winBank *ui;  // Interface utilisateur de la fenêtre / User interface of the window

    // **Méthodes pour la gestion des banques / Methods for bank management**
    void loadBankNames();             // Charger les noms de banques dans la comboBox / Load bank names into the comboBox
    void toggleEditMode(bool isNew);   // Basculer entre le mode création et modification / Toggle between creation and edit mode
    void clearBankFields();            // Vider les champs de saisie de la banque / Clear bank input fields

private slots:
    void onComboBoxSelectionChanged(int index);  // Gérer le changement de sélection dans la comboBox / Handle comboBox selection change
    void handleBankOperation();                  // Gérer l'opération de création ou modification de banque / Handle bank creation or modification operation
    void handleBankDeletion();                   // Gérer la suppression d'une banque / Handle bank deletion
};

#endif // WINBANK_H
