#include "header/mainWindowUpdate.h"
#include "header/mainwindow.h"
#include "header/objICyamApp.h"
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QLabel>
#include <QStatusBar>

// Constructeur de MainWindowUpdate / MainWindowUpdate Constructor
MainWindowUpdate::MainWindowUpdate(MainWindow *mainWindow, QObject *parent)
    : QObject(parent), m_mainWindow(mainWindow), m_comboBox(nullptr), m_treeWidget(nullptr)
{
}

// Initialise et configure les éléments de la colonne gauche / Initialize and set up left column elements
void MainWindowUpdate::setupLeftColumn(QComboBox *comboBox, QTreeWidget *treeWidget)
{
    m_comboBox = comboBox;
    m_treeWidget = treeWidget;

    initializeComboBox();  // Initialisation de la ComboBox / Initialize ComboBox
    setFontsForElements(); // Configure les polices pour les éléments / Set fonts for elements
    connectComboBox();     // Connecte la ComboBox aux changements d'index / Connect ComboBox to index changes
}

// Met à jour la barre de statut en fonction du dossier sélectionné
// Updates the status bar based on the selected folder
void MainWindowUpdate::updateStatusBar(int folderID)
{
    qDebug() << "updateStatusBar called with folderID:" << folderID;

    if (m_mainWindow) {

        // Effacer tous les widgets existants de la barre de statut pour éviter les doublons
        // Clear all existing widgets from the status bar to avoid duplicates
        m_mainWindow->statusBar()->clearMessage();

        // Affiche un message par défaut si aucun dossier n'est sélectionné
        // Shows a default message if no folder is selected
        if (folderID == -1) {
            m_mainWindow->statusBar()->showMessage(tr("📁 | Aucun dossier n'est actuellement ouvert"));
            return;
        }

        // Récupère le nom du dossier sélectionné via une requête SQL
        // Retrieves the name of the selected folder using an SQL query
        QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
        query.prepare("SELECT folder_name FROM user WHERE id_user = :id_user AND is_deleted = 0");
        query.bindValue(":id_user", folderID);

        // Affiche le nom du dossier et le chemin de la base de données en cas de succès
        // Displays the folder name and database path if the query is successful
        if (query.exec() && query.next()) {
            QString folderName = query.value("folder_name").toString();
            QString dbPath = objICyamApp::getDatabasePath();
            QString message = QString("📂 | %1 | %2 | %3 %4")
                                  .arg(folderID)
                                  .arg(folderName)
                                  .arg(tr("Base de données :"))
                                  .arg(dbPath);

            m_mainWindow->statusBar()->showMessage(message);
        } else {
            // Affiche un message d'erreur en cas d'échec de la requête
            // Displays an error message if the query fails
            qDebug() << "Erreur lors de la récupération du nom du dossier:" << query.lastError();
            m_mainWindow->statusBar()->showMessage(tr("Erreur de récupération des informations du dossier"), 5000);
        }
    }
}

// Définit les polices pour les éléments / Set fonts for elements
void MainWindowUpdate::setFontsForElements()
{
    QFont normalFont = QApplication::font();
    normalFont.setBold(false);
    m_comboBox->setFont(normalFont);
    m_treeWidget->setFont(normalFont);
}

// Initialise la ComboBox avec des options de tri par défaut / Initializes ComboBox with default sorting options
void MainWindowUpdate::initializeComboBox()
{
    m_comboBox->clear();
    m_comboBox->addItem(tr("Tri par groupe de compte"));  // Tri par groupe de compte / Sort by account group
    m_comboBox->addItem(tr("Tri par type de compte"));    // Tri par type de compte / Sort by account type
    m_comboBox->addItem(tr("Tri par banque"));            // Tri par banque / Sort by bank
    m_comboBox->setCurrentIndex(0);
}

// Connexion des changements d'index de ComboBox à la méthode appropriée / Connect ComboBox index changes to appropriate method
void MainWindowUpdate::connectComboBox()
{
    connect(m_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindowUpdate::onComboBoxIndexChanged);
}

// Gère le changement d'index dans la ComboBox et applique le tri correspondant / Handles ComboBox index changes and applies the corresponding sort
void MainWindowUpdate::onComboBoxIndexChanged(int index)
{
    switch (index) {
    case 0:
        populateTreeByAccountGroup();  // Remplit la treeWidget par groupe de compte / Populate treeWidget by account group
        break;
    case 1:
        populateTreeByAccountType();   // Remplit la treeWidget par type de compte / Populate treeWidget by account type
        break;
    case 2:
        populateTreeByBank();          // Remplit la treeWidget par banque / Populate treeWidget by bank
        break;
    default:
        break;
    }
}

// Récupère l'index courant de la comboBox
// Get current index of comboBox
int MainWindowUpdate::getComboBoxIndex() const {
    return m_comboBox ? m_comboBox->currentIndex() : -1;  // Retourne -1 si m_comboBox est nul / Return -1 if m_comboBox is null
}

// Méthode utilitaire pour exécuter une requête SQL et obtenir un seul résultat de somme
// Utility method to execute SQL query and get a single sum result
double MainWindowUpdate::executeSumQuery(const QString &queryStr, const QMap<QString, QVariant> &bindings)
{
    double result = 0.0;
    QSqlQuery query(QSqlDatabase::database("ICyamConnection"));
    query.prepare(queryStr);
    for (auto it = bindings.cbegin(); it != bindings.cend(); ++it) {
        query.bindValue(it.key(), it.value());
    }
    if (query.exec() && query.next()) {
        result = query.value(0).toDouble();
    } else {
        qDebug() << "Erreur de requête SQL:" << query.lastError();
    }
    return result;
}

// Crée et ajoute un QTreeWidgetItem avec les paramètres fournis / Create and add a QTreeWidgetItem with the provided parameters
QTreeWidgetItem *MainWindowUpdate::createItem(const QString &emoji, const QString &name, double balance,
                                              int typeCode, int id, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = (parent) ? new QTreeWidgetItem(parent) : new QTreeWidgetItem(m_treeWidget);
    item->setText(0, emoji + " " + name);
    item->setText(1, QString::number(balance, 'f', 2));
    item->setTextAlignment(1, Qt::AlignRight);
    item->setData(0, Qt::UserRole, typeCode);
    item->setData(0, Qt::UserRole + 1, id);
    return item;
}

// Définit la structure de la treeWidget pour les éléments / Set up treeWidget structure for items
void MainWindowUpdate::setupTreeWidget()
{
    m_treeWidget->clear();
    m_treeWidget->setColumnCount(2);
    m_treeWidget->setHeaderLabels({tr("Nom"), tr("Solde")});
    m_treeWidget->setColumnWidth(0, m_treeWidget->width() * 0.7); // 70% pour le nom / 70% for the name
    m_treeWidget->setColumnWidth(1, m_treeWidget->width() * 0.3); // 30% pour le solde / 30% for the balance
}

// Remplit la treeWidget par type de compte / Populate treeWidget by account type
void MainWindowUpdate::populateTreeByAccountType()
{
    int folderID = objICyamApp::getSelectedFolderId();
    if (folderID == -1) return;

    setupTreeWidget();

    QSqlQuery typeQuery(QSqlDatabase::database("ICyamConnection"));
    typeQuery.prepare("SELECT id_type, name_type FROM type_account WHERE is_deleted = 0");

    if (typeQuery.exec()) {
        while (typeQuery.next()) {
            int typeId = typeQuery.value("id_type").toInt();
            QString typeName = typeQuery.value("name_type").toString();
            QString emoji = getTypeEmoji(typeId);
            double totalBalance = executeSumQuery("SELECT SUM(balance) FROM account "
                                                  "WHERE id_type = :type_id AND id_folder = :folder_id AND is_deleted = 0",
                                                  { {":type_id", typeId}, {":folder_id", folderID} });
            QTreeWidgetItem *typeItem = createItem(emoji, typeName, totalBalance, 1, typeId);
            populateAccounts(typeItem, folderID, typeId, "id_type");
        }
    }
    m_treeWidget->expandAll();
}

// Remplit la treeWidget par banque / Populate treeWidget by bank
void MainWindowUpdate::populateTreeByBank()
{
    int folderID = objICyamApp::getSelectedFolderId();
    if (folderID == -1) return;

    setupTreeWidget();

    QSqlQuery bankQuery(QSqlDatabase::database("ICyamConnection"));
    bankQuery.prepare("SELECT id_bank, bank_name FROM bank WHERE id_folder = :folder_id AND is_deleted = 0");
    bankQuery.bindValue(":folder_id", folderID);

    if (bankQuery.exec()) {
        while (bankQuery.next()) {
            int bankId = bankQuery.value("id_bank").toInt();
            QString bankName = bankQuery.value("bank_name").toString();
            double totalBalance = executeSumQuery("SELECT SUM(balance) FROM account "
                                                  "WHERE id_bank = :bank_id AND is_deleted = 0",
                                                  { {":bank_id", bankId} });
            QTreeWidgetItem *bankItem = createItem("🏦", bankName, totalBalance, 2, bankId);
            populateAccounts(bankItem, folderID, bankId, "id_bank");
        }
    }
    m_treeWidget->expandAll();
}

// Remplit la treeWidget par groupe de compte / Populate treeWidget by account group
void MainWindowUpdate::populateTreeByAccountGroup()
{
    int folderID = objICyamApp::getSelectedFolderId();
    if (folderID == -1) return;

    setupTreeWidget();

    QSqlQuery groupQuery(QSqlDatabase::database("ICyamConnection"));
    groupQuery.prepare("SELECT id_group, name_group FROM group_account WHERE id_folder = :folder_id AND is_deleted = 0");
    groupQuery.bindValue(":folder_id", folderID);

    if (groupQuery.exec()) {
        while (groupQuery.next()) {
            int groupId = groupQuery.value("id_group").toInt();
            QString groupName = groupQuery.value("name_group").toString();
            double totalBalance = executeSumQuery("SELECT SUM(balance) FROM account "
                                                  "WHERE id_group = :group_id AND id_folder = :folder_id AND is_deleted = 0",
                                                  { {":group_id", groupId}, {":folder_id", folderID} });
            QTreeWidgetItem *groupItem = createItem("🗂️", groupName, totalBalance, 3, groupId);
            populateAccounts(groupItem, folderID, groupId, "id_group");
        }
    }

    // Comptes sans groupe / Accounts without group
    QSqlQuery ungroupedQuery(QSqlDatabase::database("ICyamConnection"));
    ungroupedQuery.prepare("SELECT id_account, account_name, balance FROM account "
                           "WHERE id_group IS NULL AND id_folder = :folder_id AND is_deleted = 0");
    ungroupedQuery.bindValue(":folder_id", folderID);

    if (ungroupedQuery.exec()) {
        while (ungroupedQuery.next()) {
            int accountId = ungroupedQuery.value("id_account").toInt();
            QString accountName = ungroupedQuery.value("account_name").toString();
            double balance = ungroupedQuery.value("balance").toDouble();
            createItem("💳", accountName, balance, 0, accountId);
        }
    }
    m_treeWidget->expandAll();
}

// Remplit les comptes pour un type de groupe donné / Populate accounts for a given group type
void MainWindowUpdate::populateAccounts(QTreeWidgetItem *parentItem, int folderID, int typeId, const QString &column)
{
    QSqlQuery accountQuery(QSqlDatabase::database("ICyamConnection"));
    accountQuery.prepare(QString("SELECT id_account, account_name, balance FROM account "
                                 "WHERE %1 = :type_id AND id_folder = :folder_id AND is_deleted = 0").arg(column));
    accountQuery.bindValue(":type_id", typeId);
    accountQuery.bindValue(":folder_id", folderID);

    if (accountQuery.exec()) {
        while (accountQuery.next()) {
            int accountId = accountQuery.value("id_account").toInt();
            QString accountName = accountQuery.value("account_name").toString();
            double balance = accountQuery.value("balance").toDouble();
            createItem("💳", accountName, balance, 0, accountId, parentItem);
        }
    }
}

// Renvoie l'emoji approprié en fonction de l'id_type / Returns the appropriate emoji based on id_type
QString MainWindowUpdate::getTypeEmoji(int typeId)
{
    switch (typeId) {
    case 1: return "💰";
    case 2: return "💸";
    case 3: return "📉";
    case 4: return "📊";
    case 5: return "🏠";
    default: return "💼";
    }
}

// Met à jour les options de la ComboBox / Updates ComboBox options
void MainWindowUpdate::updateComboBoxOptions(QComboBox* comboBox)
{
    comboBox->clear();
    comboBox->addItem(tr("Tri par groupe de compte"));
    comboBox->addItem(tr("Tri par type de compte"));
    comboBox->addItem(tr("Tri par banque"));
}

// Met à jour le solde total du dossier dans le label correspondant
// Update the total folder balance in the corresponding label
void MainWindowUpdate::updateFolderBalance(int folderID)
{
    qDebug() << "Appel de updateFolderBalance avec folderID:" << folderID;

    if (folderID == -1) {
        m_mainWindow->getLabelBalanceFolder()->setText("0.00"); // Réinitialiser le solde
        return;
    }

    double totalBalance = executeSumQuery(
        "SELECT SUM(balance) FROM account WHERE id_folder = :folder_id AND is_deleted = 0",
        { {":folder_id", folderID} }
        );

    qDebug() << "Solde total calculé pour le folderID" << folderID << ":" << totalBalance;

    m_mainWindow->getLabelBalanceFolder()->setText(QString::number(totalBalance, 'f', 2));
}
