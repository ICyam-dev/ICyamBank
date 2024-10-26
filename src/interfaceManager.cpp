#include "header/interfaceManager.h"
#include <QList>

// **Constructeur de InterfaceManager / Constructor for InterfaceManager**
InterfaceManager::InterfaceManager(QSplitter* splitter, QComboBox* comboBox, QTreeWidget* treeWidget, QWidget* parent)
    : QObject(parent)
{
    // Initialisation du gestionnaire de la colonne gauche / Initializing the left column manager
    leftColumnManager = new LeftColumnManager(comboBox, treeWidget, this);

    // Configuration du QSplitter / Setting up the QSplitter
    setupSplitter(splitter, parent);
}

// **Configuration du QSplitter / QSplitter Setup**
void InterfaceManager::setupSplitter(QSplitter* splitter, QWidget* parent)
{
    // Ajout des widgets au splitter (gauche et droite)
    // Adding left and right widgets to the splitter
    splitter->addWidget(parent->findChild<QWidget*>("widgetLeft"));
    splitter->addWidget(parent->findChild<QWidget*>("widgetRight"));

    // Définition de la taille initiale : 20% pour la gauche, 80% pour la droite
    // Setting initial size: 20% for the left, 80% for the right
    QList<int> sizes;
    sizes << parent->width() * 0.20 << parent->width() * 0.80;
    splitter->setSizes(sizes);

    // Gestion des limites de redimensionnement pour le widget gauche
    // Managing resizing limits for the left widget
    connect(splitter, &QSplitter::splitterMoved, parent, [=](int pos, int index) {
        int totalWidth = parent->width();       // Largeur totale de la fenêtre / Total window width
        int minLeftWidth = totalWidth * 0.15;   // Limite minimale à 15% pour la gauche / 15% minimum limit for the left side
        int maxLeftWidth = totalWidth * 0.40;   // Limite maximale à 40% pour la gauche / 40% maximum limit for the left side

        // Ajustement de la largeur du widget gauche pour respecter les limites
        // Adjusting the left widget width to respect the limits
        if (splitter->sizes().at(0) < minLeftWidth) {
            splitter->setSizes({minLeftWidth, totalWidth - minLeftWidth});
        } else if (splitter->sizes().at(0) > maxLeftWidth) {
            splitter->setSizes({maxLeftWidth, totalWidth - maxLeftWidth});
        }
    });
}

// **Destructeur / Destructor**
InterfaceManager::~InterfaceManager()
{
    delete leftColumnManager;
}
