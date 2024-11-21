/********************************************************************************
** Form generated from reading UI file 'winAccount.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINACCOUNT_H
#define UI_WINACCOUNT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_winAccount
{
public:
    QLabel *labelPicture;
    QLabel *labelTitle;
    QComboBox *comboBoxAccount;
    QFrame *line;
    QPushButton *pushBtnOk;
    QPushButton *pushBtnCancel;
    QPushButton *pushBtnSupp;
    QTabWidget *tabWidgetAccount;
    QWidget *tabEssentialAccount;
    QLabel *labelAccountDevise;
    QLabel *labelDesc;
    QLineEdit *lineEditAccountNumber;
    QLabel *labelAccountGroup;
    QLabel *labelAccountType;
    QComboBox *comboBoxAccountGroup;
    QLabel *labelNumber;
    QLabel *labelAccountBank;
    QLineEdit *lineEditBalance;
    QComboBox *comboBoxAccountBank;
    QLineEdit *lineEditAccountName;
    QComboBox *comboBoxAccountDevise;
    QPushButton *pushBtnAddBank;
    QCheckBox *checkBoxIncludeBalanceGroup;
    QLabel *labelName;
    QLabel *labelAccountBalance;
    QPushButton *pushBtnAddGroup;
    QTextEdit *textEditDesc;
    QComboBox *comboBoxAccountType;
    QWidget *tabContactAccount;
    QLineEdit *lineEditContactMail;
    QLabel *labelContactName;
    QLineEdit *lineEditContactName;
    QLabel *labelContactMail;
    QLineEdit *lineEditContactPhone;
    QLabel *labelContactPhone;

    void setupUi(QDialog *winAccount)
    {
        if (winAccount->objectName().isEmpty())
            winAccount->setObjectName("winAccount");
        winAccount->resize(564, 524);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        winAccount->setFont(font);
        winAccount->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        labelPicture = new QLabel(winAccount);
        labelPicture->setObjectName("labelPicture");
        labelPicture->setGeometry(QRect(10, 10, 64, 64));
        labelPicture->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/account_64.png")));
        labelTitle = new QLabel(winAccount);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(100, 10, 441, 31));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        comboBoxAccount = new QComboBox(winAccount);
        comboBoxAccount->setObjectName("comboBoxAccount");
        comboBoxAccount->setGeometry(QRect(90, 50, 471, 32));
        line = new QFrame(winAccount);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 80, 541, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        pushBtnOk = new QPushButton(winAccount);
        pushBtnOk->setObjectName("pushBtnOk");
        pushBtnOk->setGeometry(QRect(450, 480, 100, 32));
        pushBtnCancel = new QPushButton(winAccount);
        pushBtnCancel->setObjectName("pushBtnCancel");
        pushBtnCancel->setGeometry(QRect(340, 480, 100, 32));
        pushBtnSupp = new QPushButton(winAccount);
        pushBtnSupp->setObjectName("pushBtnSupp");
        pushBtnSupp->setGeometry(QRect(10, 480, 100, 32));
        tabWidgetAccount = new QTabWidget(winAccount);
        tabWidgetAccount->setObjectName("tabWidgetAccount");
        tabWidgetAccount->setGeometry(QRect(10, 100, 541, 371));
        tabEssentialAccount = new QWidget();
        tabEssentialAccount->setObjectName("tabEssentialAccount");
        labelAccountDevise = new QLabel(tabEssentialAccount);
        labelAccountDevise->setObjectName("labelAccountDevise");
        labelAccountDevise->setGeometry(QRect(285, 229, 207, 16));
        labelDesc = new QLabel(tabEssentialAccount);
        labelDesc->setObjectName("labelDesc");
        labelDesc->setGeometry(QRect(20, 101, 401, 16));
        lineEditAccountNumber = new QLineEdit(tabEssentialAccount);
        lineEditAccountNumber->setObjectName("lineEditAccountNumber");
        lineEditAccountNumber->setGeometry(QRect(20, 81, 501, 21));
        labelAccountGroup = new QLabel(tabEssentialAccount);
        labelAccountGroup->setObjectName("labelAccountGroup");
        labelAccountGroup->setGeometry(QRect(21, 283, 201, 16));
        labelAccountType = new QLabel(tabEssentialAccount);
        labelAccountType->setObjectName("labelAccountType");
        labelAccountType->setGeometry(QRect(20, 174, 207, 16));
        comboBoxAccountGroup = new QComboBox(tabEssentialAccount);
        comboBoxAccountGroup->setObjectName("comboBoxAccountGroup");
        comboBoxAccountGroup->setGeometry(QRect(16, 300, 217, 32));
        labelNumber = new QLabel(tabEssentialAccount);
        labelNumber->setObjectName("labelNumber");
        labelNumber->setGeometry(QRect(20, 61, 401, 16));
        labelAccountBank = new QLabel(tabEssentialAccount);
        labelAccountBank->setObjectName("labelAccountBank");
        labelAccountBank->setGeometry(QRect(286, 173, 201, 16));
        lineEditBalance = new QLineEdit(tabEssentialAccount);
        lineEditBalance->setObjectName("lineEditBalance");
        lineEditBalance->setGeometry(QRect(20, 250, 241, 21));
        comboBoxAccountBank = new QComboBox(tabEssentialAccount);
        comboBoxAccountBank->setObjectName("comboBoxAccountBank");
        comboBoxAccountBank->setGeometry(QRect(280, 190, 216, 32));
        lineEditAccountName = new QLineEdit(tabEssentialAccount);
        lineEditAccountName->setObjectName("lineEditAccountName");
        lineEditAccountName->setGeometry(QRect(20, 31, 501, 21));
        comboBoxAccountDevise = new QComboBox(tabEssentialAccount);
        comboBoxAccountDevise->setObjectName("comboBoxAccountDevise");
        comboBoxAccountDevise->setGeometry(QRect(277, 245, 251, 32));
        pushBtnAddBank = new QPushButton(tabEssentialAccount);
        pushBtnAddBank->setObjectName("pushBtnAddBank");
        pushBtnAddBank->setGeometry(QRect(490, 190, 33, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/winPictures/add_16.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushBtnAddBank->setIcon(icon);
        pushBtnAddBank->setAutoDefault(false);
        checkBoxIncludeBalanceGroup = new QCheckBox(tabEssentialAccount);
        checkBoxIncludeBalanceGroup->setObjectName("checkBoxIncludeBalanceGroup");
        checkBoxIncludeBalanceGroup->setGeometry(QRect(280, 305, 241, 20));
        labelName = new QLabel(tabEssentialAccount);
        labelName->setObjectName("labelName");
        labelName->setGeometry(QRect(20, 11, 251, 16));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(13);
        font1.setBold(false);
        labelName->setFont(font1);
        labelAccountBalance = new QLabel(tabEssentialAccount);
        labelAccountBalance->setObjectName("labelAccountBalance");
        labelAccountBalance->setGeometry(QRect(20, 230, 207, 16));
        pushBtnAddGroup = new QPushButton(tabEssentialAccount);
        pushBtnAddGroup->setObjectName("pushBtnAddGroup");
        pushBtnAddGroup->setGeometry(QRect(227, 300, 33, 32));
        pushBtnAddGroup->setIcon(icon);
        pushBtnAddGroup->setAutoDefault(false);
        textEditDesc = new QTextEdit(tabEssentialAccount);
        textEditDesc->setObjectName("textEditDesc");
        textEditDesc->setGeometry(QRect(20, 121, 501, 41));
        comboBoxAccountType = new QComboBox(tabEssentialAccount);
        comboBoxAccountType->setObjectName("comboBoxAccountType");
        comboBoxAccountType->setGeometry(QRect(13, 190, 261, 32));
        tabWidgetAccount->addTab(tabEssentialAccount, QString());
        tabContactAccount = new QWidget();
        tabContactAccount->setObjectName("tabContactAccount");
        lineEditContactMail = new QLineEdit(tabContactAccount);
        lineEditContactMail->setObjectName("lineEditContactMail");
        lineEditContactMail->setGeometry(QRect(10, 130, 511, 21));
        labelContactName = new QLabel(tabContactAccount);
        labelContactName->setObjectName("labelContactName");
        labelContactName->setGeometry(QRect(10, 10, 321, 16));
        labelContactName->setFont(font1);
        lineEditContactName = new QLineEdit(tabContactAccount);
        lineEditContactName->setObjectName("lineEditContactName");
        lineEditContactName->setGeometry(QRect(10, 30, 511, 21));
        labelContactMail = new QLabel(tabContactAccount);
        labelContactMail->setObjectName("labelContactMail");
        labelContactMail->setGeometry(QRect(10, 110, 351, 16));
        labelContactMail->setFont(font1);
        lineEditContactPhone = new QLineEdit(tabContactAccount);
        lineEditContactPhone->setObjectName("lineEditContactPhone");
        lineEditContactPhone->setGeometry(QRect(10, 80, 511, 21));
        labelContactPhone = new QLabel(tabContactAccount);
        labelContactPhone->setObjectName("labelContactPhone");
        labelContactPhone->setGeometry(QRect(10, 60, 331, 16));
        labelContactPhone->setFont(font1);
        tabWidgetAccount->addTab(tabContactAccount, QString());
        QWidget::setTabOrder(comboBoxAccount, lineEditAccountName);
        QWidget::setTabOrder(lineEditAccountName, lineEditAccountNumber);
        QWidget::setTabOrder(lineEditAccountNumber, textEditDesc);
        QWidget::setTabOrder(textEditDesc, comboBoxAccountType);
        QWidget::setTabOrder(comboBoxAccountType, comboBoxAccountBank);
        QWidget::setTabOrder(comboBoxAccountBank, pushBtnAddBank);
        QWidget::setTabOrder(pushBtnAddBank, comboBoxAccountDevise);
        QWidget::setTabOrder(comboBoxAccountDevise, lineEditBalance);
        QWidget::setTabOrder(lineEditBalance, comboBoxAccountGroup);
        QWidget::setTabOrder(comboBoxAccountGroup, pushBtnAddGroup);
        QWidget::setTabOrder(pushBtnAddGroup, checkBoxIncludeBalanceGroup);
        QWidget::setTabOrder(checkBoxIncludeBalanceGroup, lineEditContactName);
        QWidget::setTabOrder(lineEditContactName, lineEditContactPhone);
        QWidget::setTabOrder(lineEditContactPhone, lineEditContactMail);
        QWidget::setTabOrder(lineEditContactMail, pushBtnOk);
        QWidget::setTabOrder(pushBtnOk, pushBtnCancel);
        QWidget::setTabOrder(pushBtnCancel, pushBtnSupp);

        retranslateUi(winAccount);

        tabWidgetAccount->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(winAccount);
    } // setupUi

    void retranslateUi(QDialog *winAccount)
    {
        winAccount->setWindowTitle(QCoreApplication::translate("winAccount", "Les Comptes Bancaires", nullptr));
        labelPicture->setText(QString());
#if QT_CONFIG(tooltip)
        labelTitle->setToolTip(QCoreApplication::translate("winAccount", "Ce formulaire vous pouvez donner les d\303\251tails de vos comptes bancaires, les comptes bancaires sont rattach\303\251s \303\240 un \303\251tablissement bancaire et \303\240 un type de comptes. Vous pouvez \303\251galement le rattach\303\251 \303\240 un groupe.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelTitle->setText(QCoreApplication::translate("winAccount", "<html><head/><body><p><span style=\" font-size:24pt;\">Les Comptes Bancaires</span></p></body></html>", nullptr));
        pushBtnOk->setText(QCoreApplication::translate("winAccount", "Ok", nullptr));
        pushBtnCancel->setText(QCoreApplication::translate("winAccount", "Annuler", nullptr));
        pushBtnSupp->setText(QCoreApplication::translate("winAccount", "Supprimer", nullptr));
        labelAccountDevise->setText(QCoreApplication::translate("winAccount", "Devise :", nullptr));
        labelDesc->setText(QCoreApplication::translate("winAccount", "Courte description du compte :", nullptr));
        labelAccountGroup->setText(QCoreApplication::translate("winAccount", "Groupe :", nullptr));
        labelAccountType->setText(QCoreApplication::translate("winAccount", "Type de compte :", nullptr));
        labelNumber->setText(QCoreApplication::translate("winAccount", "Num\303\251ro ou r\303\251f\303\251rence du compte :", nullptr));
        labelAccountBank->setText(QCoreApplication::translate("winAccount", "Banque :", nullptr));
        pushBtnAddBank->setText(QString());
        checkBoxIncludeBalanceGroup->setText(QCoreApplication::translate("winAccount", "Inclure le solde dans le groupe", nullptr));
        labelName->setText(QCoreApplication::translate("winAccount", "Nom du compte en banque :", nullptr));
        labelAccountBalance->setText(QCoreApplication::translate("winAccount", "Solde du compte :", nullptr));
        pushBtnAddGroup->setText(QString());
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tabEssentialAccount), QCoreApplication::translate("winAccount", "Donn\303\251es Essentielles", nullptr));
        labelContactName->setText(QCoreApplication::translate("winAccount", "Nom, Prenom du contact :", nullptr));
        labelContactMail->setText(QCoreApplication::translate("winAccount", "Courriel du contact :", nullptr));
        labelContactPhone->setText(QCoreApplication::translate("winAccount", "N\302\260 de t\303\251l\303\251phone du contact :", nullptr));
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tabContactAccount), QCoreApplication::translate("winAccount", "Contact", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winAccount: public Ui_winAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINACCOUNT_H
