#ifndef LEFTCOLUMNMANAGER_H
#define LEFTCOLUMNMANAGER_H

#include <QObject>
#include <QComboBox>
#include <QTreeWidget>

class LeftColumnManager : public QObject
{
    Q_OBJECT

public:
    // Constructeur et destructeur / Constructor and destructor
    LeftColumnManager(QComboBox* comboBox, QTreeWidget* treeWidget, QObject* parent = nullptr);

private slots:
    // Gérer les changements dans la ComboBox / Handle changes in the ComboBox
    void onComboBoxIndexChanged(int index);

private:
    QComboBox* m_comboBox;     // ComboBox pour la gestion du tri / ComboBox for sorting management
    QTreeWidget* m_treeWidget; // TreeWidget pour afficher les éléments de la colonne gauche / TreeWidget to display left column items

    // Initialiser la ComboBox avec les options / Initialize ComboBox with options
    void initializeComboBox();
};

#endif // LEFTCOLUMNMANAGER_H
