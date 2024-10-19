#include "header/interfaceManager.h"
#include <QList>

// Constructeur / Constructor
InterfaceManager::InterfaceManager(QSplitter* splitter, QComboBox* comboBox, QTreeWidget* treeWidget, QWidget* parent)
    : QObject(parent)
{
    // Initialisation de LeftColumnManager / Initializing LeftColumnManager
    leftColumnManager = new LeftColumnManager(comboBox, treeWidget, this);

    // Configuration du QSplitter / Setting up the QSplitter
    setupSplitter(splitter, parent);
}

// Méthode pour configurer le QSplitter / Method to setup the QSplitter
void InterfaceManager::setupSplitter(QSplitter* splitter, QWidget* parent)
{
    // Ajouter les widgets gauche et droit au splitter
    // Add the left and right widgets to the splitter
    splitter->addWidget(parent->findChild<QWidget*>("widgetLeft"));
    splitter->addWidget(parent->findChild<QWidget*>("widgetRight"));

    // Définir la taille initiale des deux widgets dans le splitter (20% pour la gauche, 80% pour la droite)
    // Set the initial size of both widgets in the splitter (20% for left, 80% for right)
    QList<int> sizes;
    sizes << parent->width() * 0.20 << parent->width() * 0.80;  // Calcul des proportions / Calculating the proportions
    splitter->setSizes(sizes);

    // Limiter les dimensions lors du redimensionnement
    // Limit the dimensions during resizing
    connect(splitter, &QSplitter::splitterMoved, parent, [=](int pos, int index) {
        int totalWidth = parent->width();  // Largeur totale de la fenêtre / Total width of the window
        int minLeftWidth = totalWidth * 0.15;  // Limite de 15% pour la gauche / 15% limit for the left side
        int maxLeftWidth = totalWidth * 0.40;  // Limite de 40% pour la gauche / 40% limit for the left side

        // Vérifier et ajuster la largeur du widget gauche pour rester dans les limites
        // Check and adjust the width of the left widget to stay within the limits
        if (splitter->sizes().at(0) < minLeftWidth) {
            splitter->setSizes({minLeftWidth, totalWidth - minLeftWidth});
        } else if (splitter->sizes().at(0) > maxLeftWidth) {
            splitter->setSizes({maxLeftWidth, totalWidth - maxLeftWidth});
        }
    });
}

// Destructeur / Destructor
InterfaceManager::~InterfaceManager()
{
    delete leftColumnManager;
}
