/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionBank;
    QAction *actionAccount;
    QAction *actionGroup;
    QAction *actionOpenCreateFolder;
    QAction *actionCurrentUser;
    QWidget *centralwidget;
    QWidget *widgetLeft;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxAccount;
    QVBoxLayout *verticalLayout;
    QFrame *frameFolders;
    QVBoxLayout *verticalLayout_4;
    QComboBox *comboBoxSortAcount;
    QTreeWidget *treeWidgetAccount;
    QFrame *frameBalanceFolder;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTitleFolder;
    QLabel *labelBalanceFolder;
    QFrame *frameInfoAccount;
    QWidget *widgetRight;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidgetDetail;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *mainMenubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *mainStatusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionBank = new QAction(MainWindow);
        actionBank->setObjectName("actionBank");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/menuIcones/bank_16.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionBank->setIcon(icon);
        actionAccount = new QAction(MainWindow);
        actionAccount->setObjectName("actionAccount");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/menuIcones/account_16.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAccount->setIcon(icon1);
        actionGroup = new QAction(MainWindow);
        actionGroup->setObjectName("actionGroup");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/menuIcones/group_16.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionGroup->setIcon(icon2);
        actionOpenCreateFolder = new QAction(MainWindow);
        actionOpenCreateFolder->setObjectName("actionOpenCreateFolder");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/menuIcones/openFolder-16.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOpenCreateFolder->setIcon(icon3);
        actionCurrentUser = new QAction(MainWindow);
        actionCurrentUser->setObjectName("actionCurrentUser");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/menuIcones/user-16.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCurrentUser->setIcon(icon4);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        widgetLeft = new QWidget(centralwidget);
        widgetLeft->setObjectName("widgetLeft");
        widgetLeft->setGeometry(QRect(12, 12, 334, 335));
        sizePolicy.setHeightForWidth(widgetLeft->sizePolicy().hasHeightForWidth());
        widgetLeft->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(widgetLeft);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBoxAccount = new QGroupBox(widgetLeft);
        groupBoxAccount->setObjectName("groupBoxAccount");
        groupBoxAccount->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxAccount->sizePolicy().hasHeightForWidth());
        groupBoxAccount->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        groupBoxAccount->setFont(font);
        verticalLayout = new QVBoxLayout(groupBoxAccount);
        verticalLayout->setObjectName("verticalLayout");
        frameFolders = new QFrame(groupBoxAccount);
        frameFolders->setObjectName("frameFolders");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(4);
        sizePolicy2.setHeightForWidth(frameFolders->sizePolicy().hasHeightForWidth());
        frameFolders->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(frameFolders);
        verticalLayout_4->setObjectName("verticalLayout_4");
        comboBoxSortAcount = new QComboBox(frameFolders);
        comboBoxSortAcount->setObjectName("comboBoxSortAcount");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBoxSortAcount->sizePolicy().hasHeightForWidth());
        comboBoxSortAcount->setSizePolicy(sizePolicy3);

        verticalLayout_4->addWidget(comboBoxSortAcount);

        treeWidgetAccount = new QTreeWidget(frameFolders);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetAccount->setHeaderItem(__qtreewidgetitem);
        treeWidgetAccount->setObjectName("treeWidgetAccount");
        sizePolicy1.setHeightForWidth(treeWidgetAccount->sizePolicy().hasHeightForWidth());
        treeWidgetAccount->setSizePolicy(sizePolicy1);
        treeWidgetAccount->header()->setVisible(false);

        verticalLayout_4->addWidget(treeWidgetAccount);

        frameBalanceFolder = new QFrame(frameFolders);
        frameBalanceFolder->setObjectName("frameBalanceFolder");
        sizePolicy3.setHeightForWidth(frameBalanceFolder->sizePolicy().hasHeightForWidth());
        frameBalanceFolder->setSizePolicy(sizePolicy3);
        frameBalanceFolder->setFrameShape(QFrame::Shape::StyledPanel);
        frameBalanceFolder->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frameBalanceFolder);
        horizontalLayout->setObjectName("horizontalLayout");
        labelTitleFolder = new QLabel(frameBalanceFolder);
        labelTitleFolder->setObjectName("labelTitleFolder");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(4);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelTitleFolder->sizePolicy().hasHeightForWidth());
        labelTitleFolder->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(labelTitleFolder);

        labelBalanceFolder = new QLabel(frameBalanceFolder);
        labelBalanceFolder->setObjectName("labelBalanceFolder");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(1);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(labelBalanceFolder->sizePolicy().hasHeightForWidth());
        labelBalanceFolder->setSizePolicy(sizePolicy5);
        labelBalanceFolder->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(labelBalanceFolder);


        verticalLayout_4->addWidget(frameBalanceFolder);


        verticalLayout->addWidget(frameFolders);

        frameInfoAccount = new QFrame(groupBoxAccount);
        frameInfoAccount->setObjectName("frameInfoAccount");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(1);
        sizePolicy6.setHeightForWidth(frameInfoAccount->sizePolicy().hasHeightForWidth());
        frameInfoAccount->setSizePolicy(sizePolicy6);

        verticalLayout->addWidget(frameInfoAccount);


        verticalLayout_3->addWidget(groupBoxAccount);

        widgetRight = new QWidget(centralwidget);
        widgetRight->setObjectName("widgetRight");
        widgetRight->setGeometry(QRect(356, 12, 411, 361));
        verticalLayout_2 = new QVBoxLayout(widgetRight);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tabWidgetDetail = new QTabWidget(widgetRight);
        tabWidgetDetail->setObjectName("tabWidgetDetail");
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidgetDetail->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidgetDetail->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidgetDetail);

        MainWindow->setCentralWidget(centralwidget);
        mainMenubar = new QMenuBar(MainWindow);
        mainMenubar->setObjectName("mainMenubar");
        mainMenubar->setGeometry(QRect(0, 0, 800, 36));
        menuFile = new QMenu(mainMenubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(mainMenubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(mainMenubar);
        mainStatusbar = new QStatusBar(MainWindow);
        mainStatusbar->setObjectName("mainStatusbar");
        MainWindow->setStatusBar(mainStatusbar);

        mainMenubar->addAction(menuFile->menuAction());
        mainMenubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpenCreateFolder);
        menuFile->addSeparator();
        menuFile->addAction(actionBank);
        menuFile->addAction(actionAccount);
        menuFile->addAction(actionGroup);
        menuFile->addSeparator();
        menuFile->addAction(actionCurrentUser);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ICyamBank", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "A Propos de...", nullptr));
        actionBank->setText(QCoreApplication::translate("MainWindow", "Les Banques...", nullptr));
        actionBank->setIconText(QCoreApplication::translate("MainWindow", "Les Banques", nullptr));
        actionAccount->setText(QCoreApplication::translate("MainWindow", "Les Comptes bancaires...", nullptr));
        actionGroup->setText(QCoreApplication::translate("MainWindow", "Les Groupes de compte...", nullptr));
        actionOpenCreateFolder->setText(QCoreApplication::translate("MainWindow", "Ouvrir/Cr\303\251er un dossier...", nullptr));
        actionCurrentUser->setText(QCoreApplication::translate("MainWindow", "Utilisateur...", nullptr));
        groupBoxAccount->setTitle(QCoreApplication::translate("MainWindow", "Les Comptes Bancaires", nullptr));
        labelTitleFolder->setText(QCoreApplication::translate("MainWindow", "Solde total du dossier :", nullptr));
        labelBalanceFolder->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        tabWidgetDetail->setTabText(tabWidgetDetail->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidgetDetail->setTabText(tabWidgetDetail->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "Ficher", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Aide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
