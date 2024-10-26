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
    explicit winGroup(bool isCreationMode = false, QWidget *parent = nullptr);
    ~winGroup();

    // Définir le mode de la fenêtre (création seulement ou non)
    // Set window mode (creation-only or not)
    void setMode(bool creationOnly);

protected:
    // Événement de fermeture personnalisé pour désactiver la fermeture par les boutons système
    // Custom close event to prevent closing with system buttons
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::winGroup *ui;
    bool creationModeOnly = false;  // Indicate si la fenêtre est en mode "création uniquement" / Indicates if window is in "creation only" mode

    // **Méthodes de gestion de la fenêtre / Window Management Methods**
    void loadGroupNames();            // Charger les noms des groupes dans la ComboBox / Load group names into the ComboBox
    void setNewGroupMode();            // Forcer la ComboBox en mode "Nouveau Groupe" / Force ComboBox to "New Group" mode
    void toggleEditMode(bool isNew);   // Basculer entre les modes création et édition / Toggle between creation and edit modes
    void clearGroupFields();           // Effacer les champs de la fenêtre / Clear the window fields

private slots:
    void onComboBoxSelectionChanged(int index); // Gérer la sélection dans la ComboBox / Handle selection in the ComboBox
    void handleGroupOperation();                // Gérer la création ou la mise à jour d'un groupe / Handle group creation or update
    void handleGroupDeletion();                 // Gérer la suppression d'un groupe / Handle group deletion
};

#endif // WINGROUP_H
