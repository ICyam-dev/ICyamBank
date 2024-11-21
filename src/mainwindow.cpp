#include "header/mainwindow.h"
#include "header/mainWindowUpdate.h"  // Inclusion de mainWindowUpdate / Inclusion of mainWindowUpdate
#include "header/objICyamApp.h"       // Inclusion de objICyamApp pour méthodes centralisées / Inclusion of objICyamApp for centralized methods
#include "header/winCurrentUser.h"
#include "ui_mainwindow.h"
#include "header/winAbout.h"          // Inclusion de la fenêtre WinAbout / Inclusion of WinAbout window
#include "header/winAccount.h"        // Inclusion de winAccount / Inclusion of winAccount
#include "header/winGroup.h"          // Inclure winGroup / Include winGroup
#include "header/winUser.h"           // Inclure winUser / Include winUser
#include "header/winBank.h"           // Inclure winBank / Include winBank
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QTimer>
#include <QSplitter>
#include <QList>
#include <QMenu>
#include <QAction>
#include <QTreeWidget>
#include <QContextMenuEvent>
#include <QPoint>
#include <QEvent>

// Constructeur de la fenêtre principale / Main window constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
, ui(new Ui::MainWindow)
, m_updater(this)
{
    ui->setupUi(this);

    // Afficher les pilotes disponibles pour confirmation / Display available drivers for confirmation
    qDebug() << "Drivers disponibles:" << QSqlDatabase::drivers();

    // Créer et configurer le splitter principal / Create and configure the main splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(ui->widgetLeft);  // Ajoute le widget gauche / Add left widget
    splitter->addWidget(ui->widgetRight); // Ajoute le widget droit / Add right widget
    ui->centralwidget->setLayout(new QVBoxLayout);  // Remplace le layout de `centralwidget` / Replace `centralwidget` layout
    ui->centralwidget->layout()->addWidget(splitter); // Ajoute le splitter / Add splitter

    // Configurer la taille initiale des panneaux du splitter / Configure the initial size of the splitter panels
    QList<int> sizes;
    sizes << width() * 0.20 << width() * 0.80;
    splitter->setSizes(sizes);

    // Limites de redimensionnement pour le widget gauche / Set resizing limits for the left widget
    connect(splitter, &QSplitter::splitterMoved, this, [=](int pos, int index) {
        int totalWidth = width();
        int minLeftWidth = totalWidth * 0.15;
        int maxLeftWidth = totalWidth * 0.40;

        if (splitter->sizes().at(0) < minLeftWidth) {
            splitter->setSizes({minLeftWidth, totalWidth - minLeftWidth});
        } else if (splitter->sizes().at(0) > maxLeftWidth) {
            splitter->setSizes({maxLeftWidth, totalWidth - maxLeftWidth});
        }
    });

    // Configuration de la colonne de gauche / Setup of the left column
    m_updater.setupLeftColumn(ui->comboBoxSortAcount, ui->treeWidgetAccount);

    // Rafraîchir la comboBox avec les options de tri dès l'ouverture / Refresh the comboBox with sorting options on opening
    m_updater.updateComboBoxOptions(ui->comboBoxSortAcount);

    // Ouvrir la fenêtre utilisateur après l'affichage de MainWindow / Open the user dialog after MainWindow is shown
    QTimer::singleShot(100, this, &MainWindow::openUserDialog);

    // Connexions explicites pour chaque action / Explicit connections for each action
    connect(ui->actionOpenCreateFolder, &QAction::triggered, this, &MainWindow::openCreateFolder);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
    connect(ui->actionBank, &QAction::triggered, this, &MainWindow::openBankWindow);
    connect(ui->actionAccount, &QAction::triggered, this, &MainWindow::openAccountWindow);
    connect(ui->actionGroup, &QAction::triggered, this, &MainWindow::openGroupWindow);
    connect(ui->actionCurrentUser, &QAction::triggered, this, &MainWindow::openCurrentUser);
    connect(ui->treeWidgetAccount, &QTreeWidget::itemClicked, this, &MainWindow::onTreeViewItemClicked);

    initializeContextMenuTreeView();  // Initialisation du menu contextuel pour le treeWidgetAccount / Initialize the context menu for treeWidgetAccount
}

// Récupère la comboBox pour le tri des comptes / Retrieve the account sorting comboBox
QComboBox* MainWindow::getComboBoxSortAccount() const {
    return ui->comboBoxSortAcount;
}

// Récupère l'instance de MainWindowUpdate / Retrieve the instance of MainWindowUpdate
MainWindowUpdate* MainWindow::getMainWindowUpdater() {
    return &m_updater;
}

// Méthode pour rafraîchir l'interface / Method to refresh the interface
void MainWindow::refreshInterface()
{
    qDebug() << "Appel de refreshInterface";  // Debug pour vérifier que la méthode est bien appelée

    int folderID = objICyamApp::getSelectedFolderId();

    // Vérifier si aucun dossier n'est sélectionné / Check if no folder is selected
    if (folderID == -1) {
        // Désactiver uniquement les éléments spécifiés / Disable only specified elements
        ui->comboBoxSortAcount->setEnabled(false);
        ui->treeWidgetAccount->setEnabled(false);
        ui->tabWidgetDetail->setEnabled(false);

        // Afficher le message d'absence de dossier dans la barre de statut / Display "no folder" message in the status bar
        m_updater.updateStatusBar(folderID);

        return;  // Ne pas continuer si aucun dossier n'est sélectionné / Do not continue if no folder is selected
    }

    // Si un dossier est sélectionné, activer les éléments / If a folder is selected, enable elements
    ui->comboBoxSortAcount->setEnabled(true);
    ui->treeWidgetAccount->setEnabled(true);
    ui->tabWidgetDetail->setEnabled(true);

    qDebug() << "Rafraîchissement de l'interface en cours avec folderID:" << folderID;

    // Mettre à jour la barre de statut via MainWindowUpdate / Update the status bar via MainWindowUpdate
    m_updater.updateStatusBar(folderID);

    // Appeler la mise à jour du solde via MainWindowUpdate
    // Call balance update via MainWindowUpdate
    m_updater.updateFolderBalance(folderID);

    // Activer ou désactiver les actions en fonction de l'état du dossier sélectionné / Enable or disable actions based on folder status
    updateActions(folderID != -1);
}

// Méthode pour activer ou désactiver certaines actions (menu, boutons, etc.) / Method to enable or disable certain actions (menu, buttons, etc.)
void MainWindow::updateActions(bool enabled)
{
    // Activer ou désactiver les actions principales / Enable or disable main actions
    ui->actionBank->setEnabled(enabled);
    ui->actionAccount->setEnabled(enabled);
    ui->actionGroup->setEnabled(enabled);
    ui->actionCurrentUser->setEnabled(enabled);

    // Gérer le cas où aucun dossier n'est sélectionné / Handle the case when no folder is selected
    if (!enabled) {
        // Désactiver les éléments spécifiques de l'interface / Disable specific interface elements
        ui->comboBoxSortAcount->setEnabled(false);
        ui->treeWidgetAccount->setEnabled(false);
        ui->tabWidgetDetail->setEnabled(false);

        // Afficher le message de dossier non sélectionné dans la barre de statut / Display "no folder selected" message in the status bar
        statusBar()->showMessage(tr("📁 | Aucun dossier n'est actuellement ouvert"));
    } else {
        // Si un dossier est sélectionné, activer les éléments / If a folder is selected, enable elements
        ui->comboBoxSortAcount->setEnabled(true);
        ui->treeWidgetAccount->setEnabled(true);
        ui->tabWidgetDetail->setEnabled(true);

        // Mettre à jour le message de la barre de statut pour afficher le dossier en cours / Update status bar message to display current folder
        int folderID = objICyamApp::getSelectedFolderId();
        m_updater.updateStatusBar(folderID);
    }
}

// Slot déclenché au clic d'un élément de la treeView / Slot triggered on treeView item click
void MainWindow::onTreeViewItemClicked(QTreeWidgetItem *item, int column)
{
    // Récupérer l'identifiant de type de l'élément
    // Retrieve the item type identifier
    int itemType = item->data(0, Qt::UserRole).toInt();

    // Récupérer l'ID de l'élément dans la base de données
    // Retrieve the item's database ID
    int itemId = item->data(0, Qt::UserRole + 1).toInt();

    // Définir le texte pour le type en fonction du code
    // Define text for the type based on the code
    QString typeText;
    switch (itemType) {
    case 0: typeText = "Compte"; break;
    case 1: typeText = "Type de compte"; break;
    case 2: typeText = "Banque"; break;
    case 3: typeText = "Groupe de compte"; break;
    default: typeText = "Inconnu"; break;
    }

    // Récupérer le nom de l'élément
    // Retrieve the item name
    QString itemName = item->text(0);

    // Afficher une popup avec le type, le nom et l'ID de l'élément
    // Show a popup with the type, name, and ID of the item
    QMessageBox::information(this, "Informations sur l'élément",
                             QString("Type : %1\nNom : %2\nID : %3")
                                 .arg(typeText, itemName, QString::number(itemId)));
}

// Ouverture automatique de la fenêtre utilisateur après affichage / Automatically open the user dialog after display
void MainWindow::openUserDialog()
{
    winUser userDialog(this);
    userDialog.exec();

    // Rafraîchir l'interface après la fermeture de winUser
    refreshInterface();
}

// Slot pour l'ouverture manuelle de la fenêtre winUser / Slot for manually opening the winUser dialog
void MainWindow::openCreateFolder()
{
    winUser userDialog(this);
    userDialog.exec();

    // Rafraîchir l'interface après la fermeture de winUser
    refreshInterface();
}

// Afficher la fenêtre "À propos" en mode modal / Display the "About" window in modal mode
void MainWindow::showAbout()
{
    WinAbout aboutDialog(this);
    aboutDialog.setModal(true);
    aboutDialog.exec();
}

// Ouverture de la fenêtre bancaire en mode hybride / Open the banking window in hybrid mode
void MainWindow::openBankWindow()
{
    winBank *bankWindow = new winBank(false, this);
    bankWindow->exec();
    delete bankWindow; // Nettoyer après usage / Clean up after use
}

// Ouverture de la fenêtre de gestion des comptes / Open the account management window
void MainWindow::openAccountWindow()
{
    winAccount *accountWindow = new winAccount(this);
    accountWindow->exec();
    delete accountWindow; // Nettoyer après usage / Clean up after use
}

// Ouverture de la fenêtre de gestion des groupes / Open the group management window
void MainWindow::openGroupWindow()
{
    winGroup *groupWindow = new winGroup(false, this);
    groupWindow->exec();
    delete groupWindow; // Nettoyer après usage / Clean up after use
}

// Ouverture de la fenêtre des informations utilisateur en cours / Open the current user information window
void MainWindow::openCurrentUser()
{
    winCurrentUser currentUserDialog(this);
    currentUserDialog.exec();
}

// Déclaration du menu contextuel et des actions dans le constructeur de MainWindow
// Declaration of the context menu and actions in the MainWindow constructor
void MainWindow::initializeContextMenuTreeView()
{
    ui->treeWidgetAccount->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidgetAccount, &QTreeWidget::customContextMenuRequested,
            this, &MainWindow::showContextMenu);

    // Initialisation des actions du menu contextuel / Initialization of context menu actions
    m_actionNewBank = new QAction(tr("Nouvelle banque..."), this);
    m_actionEditBank = new QAction(tr("Modifier la banque..."), this);
    m_actionDeleteBank = new QAction(tr("Supprimer la banque..."), this);
    m_actionNewGroup = new QAction(tr("Nouveau groupe..."), this);
    m_actionEditGroup = new QAction(tr("Modifier le groupe..."), this);
    m_actionDeleteGroup = new QAction(tr("Supprimer le groupe..."), this);
    m_actionNewAccount = new QAction(tr("Nouveau compte..."), this);
    m_actionEditAccount = new QAction(tr("Modifier le compte..."), this);
    m_actionDeleteAccount = new QAction(tr("Supprimer le compte..."), this);
}

// Affichage et gestion du menu contextuel
// Display and management of the context menu
void MainWindow::showContextMenu(const QPoint &pos)
{
    // Désactivation par défaut de toutes les actions / Disable all actions by default
    QList<QAction*> actions = {m_actionNewBank, m_actionEditBank, m_actionDeleteBank,
                                m_actionNewGroup, m_actionEditGroup, m_actionDeleteGroup,
                                m_actionNewAccount, m_actionEditAccount, m_actionDeleteAccount};
    for (QAction* action : actions) {
        action->setEnabled(false);
    }

    // Détection de l'index de la comboBox et de l'élément sous le clic / Detect comboBox index and item under the click
    int comboIndex = m_updater.getComboBoxIndex();
    QTreeWidgetItem *item = ui->treeWidgetAccount->itemAt(pos);
    int itemType = item ? item->data(0, Qt::UserRole).toInt() : -1;

    // Gestion des actions selon l'index de comboBox et le type de clic / Manage actions according to comboBox index and click type
    if (comboIndex == 0) { // Tri par groupe de compte / Sort by account group
        if (!item) { // Clic en dehors de tout élément / Click outside any item
            m_actionNewGroup->setEnabled(true);
            m_actionNewAccount->setEnabled(true);
        } else if (itemType == 0) { // Clic sur un compte / Click on an account
            m_actionNewGroup->setEnabled(true);
            m_actionNewAccount->setEnabled(true);
            m_actionEditAccount->setEnabled(true);
            m_actionDeleteAccount->setEnabled(true);
        } else if (itemType == 3) { // Clic sur un groupe / Click on a group
            m_actionNewGroup->setEnabled(true);
            m_actionEditGroup->setEnabled(true);
            m_actionDeleteGroup->setEnabled(true);
            m_actionNewAccount->setEnabled(true);
        }
    } else if (comboIndex == 1) { // Tri par type de compte / Sort by account type
        if (!item) { // Clic en dehors de tout élément / Click outside any item
            m_actionNewAccount->setEnabled(true);
        } else if (itemType == 1) { // Clic sur un type de compte / Click on an account type
            m_actionNewAccount->setEnabled(true);
        } else if (itemType == 0) { // Clic sur un compte / Click on an account
            m_actionNewAccount->setEnabled(true);
            m_actionEditAccount->setEnabled(true);
            m_actionDeleteAccount->setEnabled(true);
        }
    } else if (comboIndex == 2) { // Tri par banque / Sort by bank
        if (!item) { // Clic en dehors de tout élément / Click outside any item
            m_actionNewBank->setEnabled(true);
            m_actionNewAccount->setEnabled(true);
        } else if (itemType == 2) { // Clic sur une banque / Click on a bank
            m_actionNewBank->setEnabled(true);
            m_actionEditBank->setEnabled(true);
            m_actionDeleteBank->setEnabled(true);
            m_actionNewAccount->setEnabled(true);
        } else if (itemType == 0) { // Clic sur un compte / Click on an account
            m_actionNewBank->setEnabled(true);
            m_actionNewAccount->setEnabled(true);
            m_actionEditAccount->setEnabled(true);
            m_actionDeleteAccount->setEnabled(true);
        }
    }

    // Création et affichage du menu contextuel avec les actions activées / Creation and display of the context menu with enabled actions
    QMenu contextMenu(this);
    contextMenu.addAction(m_actionNewBank);
    contextMenu.addAction(m_actionEditBank);
    contextMenu.addAction(m_actionDeleteBank);
    contextMenu.addSeparator();
    contextMenu.addAction(m_actionNewGroup);
    contextMenu.addAction(m_actionEditGroup);
    contextMenu.addAction(m_actionDeleteGroup);
    contextMenu.addSeparator();
    contextMenu.addAction(m_actionNewAccount);
    contextMenu.addAction(m_actionEditAccount);
    contextMenu.addAction(m_actionDeleteAccount);

    contextMenu.exec(ui->treeWidgetAccount->viewport()->mapToGlobal(pos));
}

// Destructeur / Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
