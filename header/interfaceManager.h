#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include <QObject>
#include <QComboBox>
#include <QTreeWidget>
#include <QSplitter>
#include "leftcolumnManager.h"

class InterfaceManager : public QObject
{
    Q_OBJECT

public:
    // Constructeur et destructeur / Constructor and destructor
    InterfaceManager(QSplitter* splitter, QComboBox* comboBox, QTreeWidget* treeWidget, QWidget* parent = nullptr);
    ~InterfaceManager();

private:
    // Gestionnaire pour la colonne gauche de l'interface / Manager for the left column of the interface
    LeftColumnManager* leftColumnManager;

    // Configurer le QSplitter pour la mise en page de l'interface / Set up QSplitter for interface layout
    void setupSplitter(QSplitter* splitter, QWidget* parent);
};

#endif // INTERFACEMANAGER_H
