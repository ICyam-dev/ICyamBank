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
    InterfaceManager(QSplitter* splitter, QComboBox* comboBox, QTreeWidget* treeWidget, QWidget* parent = nullptr);
    ~InterfaceManager();

private:
    LeftColumnManager* leftColumnManager;  // Pointeur vers le gestionnaire de la colonne gauche / Pointer to the left column manager
    void setupSplitter(QSplitter* splitter, QWidget* parent);  // Configure le QSplitter avec les limites et les proportions / Set up the QSplitter with limits and proportions
};

#endif // INTERFACEMANAGER_H
