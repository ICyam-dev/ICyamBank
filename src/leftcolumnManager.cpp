#include "header/leftcolumnManager.h"
#include <QTranslator>
#include <QApplication>

LeftColumnManager::LeftColumnManager(QComboBox* comboBoxSortAcount, QTreeWidget* treeWidgetAccount, QObject* parent)
    : QObject(parent), m_comboBox(comboBoxSortAcount), m_treeWidget(treeWidgetAccount)
{
    // Initialisation de la ComboBox / Initialize the ComboBox
    initializeComboBox();

    // Appliquer la police normale (sans gras) à la ComboBox et à la TreeView
    // Apply the normal (non-bold) font to the ComboBox and TreeView
    QFont normalFont = QApplication::font();
    normalFont.setBold(false);  // Désactiver le gras / Disable bold
    m_comboBox->setFont(normalFont);  // Appliquer à la ComboBox / Apply to ComboBox
    m_treeWidget->setFont(normalFont);  // Appliquer à la TreeView / Apply to TreeView

    // Connexion du signal pour surveiller les changements dans la ComboBox
    // Connect signal to track changes in the ComboBox
    connect(m_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &LeftColumnManager::onComboBoxIndexChanged);
}

void LeftColumnManager::initializeComboBox()
{
    // Ajout des éléments traduisibles à la ComboBox
    // Add translatable items to the ComboBox
    m_comboBox->addItem(tr("Tri par groupe de compte"));  // Option 1
    m_comboBox->addItem(tr("Tri par type de compte"));    // Option 2
    m_comboBox->addItem(tr("Tri par banque"));            // Option 3

    // Définir l'option par défaut (première option)
    // Set the default option (first option)
    m_comboBox->setCurrentIndex(0);
}

void LeftColumnManager::onComboBoxIndexChanged(int index)
{
    // Gestion des changements en fonction de l'option sélectionnée
    // Handle changes based on the selected option
    switch (index) {
    case 0:
        // Tri par groupe de compte sélectionné
        // Sorting by account group selected
        // Ajouter la logique plus tard
        // Add the logic later
        break;
    case 1:
        // Tri par type de compte sélectionné
        // Sorting by account type selected
        break;
    case 2:
        // Tri par banque sélectionné
        // Sorting by bank selected
        break;
    default:
        break;
    }
}
