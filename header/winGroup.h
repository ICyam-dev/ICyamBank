#ifndef WINGROUP_H
#define WINGROUP_H

#include <QDialog>
#include <QCloseEvent>   // Inclusion pour gérer l'événement de fermeture / Inclusion to handle close event

namespace Ui {
class winGroup;
}

class winGroup : public QDialog
{
    Q_OBJECT

public:
    explicit winGroup(QWidget *parent = nullptr);
    ~winGroup();
    void setNewGroupMode();  // Méthode pour forcer le mode "Création" / Method to force "Creation" mode

protected:
    void closeEvent(QCloseEvent *event) override;  // Méthode pour empêcher la fermeture avec les boutons de contrôle

private:
    Ui::winGroup *ui;

    // Méthodes pour gérer la fenêtre / Methods to manage the window
    void loadGroupNames();        // Charger les groupes dans la ComboBox / Load groups into the ComboBox
    void toggleEditMode(bool isNew); // Basculer entre mode création et modification / Toggle between creation and edit mode
    void clearGroupFields();      // Méthode pour vider les champs du groupe / Method to clear the group fields

private slots:
    void onComboBoxSelectionChanged(int index); // Slot pour gérer le changement de sélection dans la comboBox / Slot to handle comboBox selection change
    void handleGroupOperation();  // Gérer l'opération de création ou de modification du groupe / Handle group creation or modification
    void handleGroupDeletion();   // Gérer la suppression d'un groupe / Handle group deletion
};

#endif // WINGROUP_H
