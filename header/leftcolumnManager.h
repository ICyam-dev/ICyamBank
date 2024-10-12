#ifndef LEFTCOLUMNMANAGER_H
#define LEFTCOLUMNMANAGER_H

#include <QObject>
#include <QComboBox>
#include <QTreeWidget>

class LeftColumnManager : public QObject
{
    Q_OBJECT

public:
    // Constructeur / Constructor
    LeftColumnManager(QComboBox* comboBox, QTreeWidget* treeWidget, QObject* parent = nullptr);

private slots:
    // Méthode pour gérer les changements de la ComboBox / Method to handle ComboBox changes
    void onComboBoxIndexChanged(int index);

private:
    QComboBox* m_comboBox;    // ComboBox pour le tri / ComboBox for sorting
    QTreeWidget* m_treeWidget; // TreeView pour afficher les comptes / TreeView for displaying accounts

    // Méthode pour initialiser la ComboBox / Method to initialize the ComboBox
    void initializeComboBox();
};

#endif // LEFTCOLUMNMANAGER_H
