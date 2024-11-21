#ifndef MAINWINDOWUPDATE_H
#define MAINWINDOWUPDATE_H

#include <QObject>
#include <QComboBox>
#include <QTreeWidget>

class MainWindow; // Déclaration anticipée de MainWindow

class MainWindowUpdate : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowUpdate(MainWindow *mainWindow, QObject *parent = nullptr);

    // Configure la colonne de gauche avec ComboBox et TreeWidget
    // Sets up left column with ComboBox and TreeWidget
    void setupLeftColumn(QComboBox *comboBox, QTreeWidget *treeWidget);

    // Met à jour les options de la ComboBox
    // Updates ComboBox options
    void updateComboBoxOptions(QComboBox *comboBox);

    // Met à jour la barre de statut en fonction du dossier sélectionné
    // Updates the status bar based on the selected folder
    void updateStatusBar(int folderID);

    // Met à jour le solde total du dossier dans le label correspondant
    // Update the total folder balance in the corresponding label
    void updateFolderBalance(int folderID);

    int getComboBoxIndex() const;  // Récupère l'index courant de la comboBox / Get current index of comboBox

private:
    // Initialise la ComboBox avec les options de tri par défaut
    // Initializes the ComboBox with default sorting options
    void initializeComboBox();

    // Définit les polices pour les éléments de la ComboBox et TreeWidget
    // Sets fonts for ComboBox and TreeWidget elements
    void setFontsForElements();

    // Connecte la ComboBox pour détecter les changements d'index
    // Connects the ComboBox to detect index changes
    void connectComboBox();

    // Gère les changements d'index de la ComboBox
    // Handles index changes of the ComboBox
    void onComboBoxIndexChanged(int index);

    // Utilitaire pour exécuter une requête SQL de somme avec des paramètres
    // Utility to execute a sum SQL query with parameters
    double executeSumQuery(const QString &queryStr, const QMap<QString, QVariant> &bindings);

    // Crée un élément QTreeWidgetItem avec les informations spécifiées
    // Creates a QTreeWidgetItem with specified information
    QTreeWidgetItem *createItem(const QString &emoji, const QString &name, double balance,
                                int typeCode, int id, QTreeWidgetItem *parent = nullptr);

    // Configure la structure de la TreeWidget pour les éléments
    // Sets up the TreeWidget structure for elements
    void setupTreeWidget();

    // Remplit la TreeWidget par type de compte
    // Populates TreeWidget by account type
    void populateTreeByAccountType();

    // Remplit la TreeWidget par banque
    // Populates TreeWidget by bank
    void populateTreeByBank();

    // Remplit la TreeWidget par groupe de compte
    // Populates TreeWidget by account group
    void populateTreeByAccountGroup();

    // Remplit les comptes pour un type de groupe donné (par type, banque, ou groupe)
    // Populates accounts for a given group type (by type, bank, or group)
    void populateAccounts(QTreeWidgetItem *parentItem, int folderID, int typeId, const QString &column);

    // Renvoie l'emoji approprié pour un type spécifique
    // Returns the appropriate emoji for a specific type
    QString getTypeEmoji(int typeId);

    MainWindow *m_mainWindow;    // Pointeur vers l'objet MainWindow / Pointer to MainWindow object
    QComboBox *m_comboBox;       // ComboBox pour la gestion de la colonne gauche / ComboBox for left column management
    QTreeWidget *m_treeWidget;   // TreeWidget pour la gestion de la colonne gauche / TreeWidget for left column management
};

#endif // MAINWINDOWUPDATE_H
