/********************************************************************************
** Form generated from reading UI file 'winBank.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINBANK_H
#define UI_WINBANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_winBank
{
public:
    QLabel *labelBank;
    QLabel *labelDesc;
    QFrame *line;
    QLabel *labelBankName;
    QLabel *labelBankAdress;
    QLineEdit *lineEditBankName;
    QLineEdit *lineEditBankAdr1;
    QLineEdit *lineEditBankAdr2;
    QLineEdit *lineEditBankAdr3;
    QLabel *labelBankPhone;
    QLabel *labelBankMail;
    QLineEdit *lineEditBankPhone;
    QLineEdit *lineEditBankMail;
    QGroupBox *groupBoxContactBank;
    QLabel *labelContactName;
    QLineEdit *lineEditContactName;
    QLabel *labelContactPhone;
    QLabel *labelContactMail;
    QLineEdit *lineEditContactPhone;
    QLineEdit *lineEditContactMail;
    QPushButton *pushBtnOK;
    QPushButton *pushBtnCancel;
    QComboBox *comboBoxBank;
    QPushButton *pushBtnSupp;

    void setupUi(QDialog *winBank)
    {
        if (winBank->objectName().isEmpty())
            winBank->setObjectName("winBank");
        winBank->resize(630, 520);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        winBank->setFont(font);
        labelBank = new QLabel(winBank);
        labelBank->setObjectName("labelBank");
        labelBank->setGeometry(QRect(10, 10, 128, 128));
        labelBank->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/bank_128.png")));
        labelDesc = new QLabel(winBank);
        labelDesc->setObjectName("labelDesc");
        labelDesc->setGeometry(QRect(150, 10, 461, 91));
        labelDesc->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        line = new QFrame(winBank);
        line->setObjectName("line");
        line->setGeometry(QRect(150, 130, 461, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        labelBankName = new QLabel(winBank);
        labelBankName->setObjectName("labelBankName");
        labelBankName->setGeometry(QRect(150, 150, 211, 16));
        labelBankAdress = new QLabel(winBank);
        labelBankAdress->setObjectName("labelBankAdress");
        labelBankAdress->setGeometry(QRect(150, 200, 311, 16));
        lineEditBankName = new QLineEdit(winBank);
        lineEditBankName->setObjectName("lineEditBankName");
        lineEditBankName->setGeometry(QRect(150, 170, 461, 21));
        lineEditBankAdr1 = new QLineEdit(winBank);
        lineEditBankAdr1->setObjectName("lineEditBankAdr1");
        lineEditBankAdr1->setGeometry(QRect(150, 220, 461, 21));
        lineEditBankAdr2 = new QLineEdit(winBank);
        lineEditBankAdr2->setObjectName("lineEditBankAdr2");
        lineEditBankAdr2->setGeometry(QRect(150, 240, 461, 21));
        lineEditBankAdr3 = new QLineEdit(winBank);
        lineEditBankAdr3->setObjectName("lineEditBankAdr3");
        lineEditBankAdr3->setGeometry(QRect(150, 260, 461, 21));
        labelBankPhone = new QLabel(winBank);
        labelBankPhone->setObjectName("labelBankPhone");
        labelBankPhone->setGeometry(QRect(150, 290, 211, 16));
        labelBankMail = new QLabel(winBank);
        labelBankMail->setObjectName("labelBankMail");
        labelBankMail->setGeometry(QRect(390, 290, 221, 16));
        lineEditBankPhone = new QLineEdit(winBank);
        lineEditBankPhone->setObjectName("lineEditBankPhone");
        lineEditBankPhone->setGeometry(QRect(150, 310, 221, 21));
        lineEditBankMail = new QLineEdit(winBank);
        lineEditBankMail->setObjectName("lineEditBankMail");
        lineEditBankMail->setGeometry(QRect(390, 310, 221, 21));
        groupBoxContactBank = new QGroupBox(winBank);
        groupBoxContactBank->setObjectName("groupBoxContactBank");
        groupBoxContactBank->setGeometry(QRect(150, 340, 461, 131));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(13);
        font1.setBold(true);
        groupBoxContactBank->setFont(font1);
        labelContactName = new QLabel(groupBoxContactBank);
        labelContactName->setObjectName("labelContactName");
        labelContactName->setGeometry(QRect(10, 30, 211, 16));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(13);
        font2.setBold(false);
        labelContactName->setFont(font2);
        lineEditContactName = new QLineEdit(groupBoxContactBank);
        lineEditContactName->setObjectName("lineEditContactName");
        lineEditContactName->setGeometry(QRect(10, 50, 441, 21));
        labelContactPhone = new QLabel(groupBoxContactBank);
        labelContactPhone->setObjectName("labelContactPhone");
        labelContactPhone->setGeometry(QRect(10, 80, 191, 16));
        labelContactPhone->setFont(font2);
        labelContactMail = new QLabel(groupBoxContactBank);
        labelContactMail->setObjectName("labelContactMail");
        labelContactMail->setGeometry(QRect(240, 80, 181, 16));
        labelContactMail->setFont(font2);
        lineEditContactPhone = new QLineEdit(groupBoxContactBank);
        lineEditContactPhone->setObjectName("lineEditContactPhone");
        lineEditContactPhone->setGeometry(QRect(10, 100, 211, 21));
        lineEditContactMail = new QLineEdit(groupBoxContactBank);
        lineEditContactMail->setObjectName("lineEditContactMail");
        lineEditContactMail->setGeometry(QRect(240, 100, 211, 21));
        pushBtnOK = new QPushButton(winBank);
        pushBtnOK->setObjectName("pushBtnOK");
        pushBtnOK->setGeometry(QRect(510, 480, 100, 32));
        pushBtnCancel = new QPushButton(winBank);
        pushBtnCancel->setObjectName("pushBtnCancel");
        pushBtnCancel->setGeometry(QRect(400, 480, 100, 32));
        comboBoxBank = new QComboBox(winBank);
        comboBoxBank->setObjectName("comboBoxBank");
        comboBoxBank->setGeometry(QRect(140, 100, 471, 32));
        pushBtnSupp = new QPushButton(winBank);
        pushBtnSupp->setObjectName("pushBtnSupp");
        pushBtnSupp->setGeometry(QRect(150, 480, 100, 32));

        retranslateUi(winBank);

        QMetaObject::connectSlotsByName(winBank);
    } // setupUi

    void retranslateUi(QDialog *winBank)
    {
        winBank->setWindowTitle(QCoreApplication::translate("winBank", "Nouvelle Banque", nullptr));
        labelBank->setText(QString());
        labelDesc->setText(QCoreApplication::translate("winBank", "<html><head/><body><p><span style=\" font-size:24pt;\">Les Etablissements Bancaires</span></p><p>Dans ce formulaire vous pouvez donner des d\303\251tails sur vos \303\251tablissements<br/>bancaires. Cela peux \303\252tre utilise de pouvoir envoyer un mail ou t\303\251l\303\251phoner a<br/>sa banque ou personnaliser vos rapports</p></body></html>", nullptr));
        labelBankName->setText(QCoreApplication::translate("winBank", "Nom de l'\303\251tablissement bancaire :", nullptr));
        labelBankAdress->setText(QCoreApplication::translate("winBank", "Adresse de l'\303\251tablissement bancaire :", nullptr));
        labelBankPhone->setText(QCoreApplication::translate("winBank", "T\303\251l\303\251phone de la banque :", nullptr));
        labelBankMail->setText(QCoreApplication::translate("winBank", "Mail de la banque :", nullptr));
        groupBoxContactBank->setTitle(QCoreApplication::translate("winBank", "Contact \303\240 la banque :", nullptr));
        labelContactName->setText(QCoreApplication::translate("winBank", "Nom et pr\303\251nom du contact :", nullptr));
        labelContactPhone->setText(QCoreApplication::translate("winBank", "T\303\251l\303\251phone :", nullptr));
        labelContactMail->setText(QCoreApplication::translate("winBank", "Mail :", nullptr));
        pushBtnOK->setText(QCoreApplication::translate("winBank", "Ok", nullptr));
        pushBtnCancel->setText(QCoreApplication::translate("winBank", "Annuler", nullptr));
        pushBtnSupp->setText(QCoreApplication::translate("winBank", "Supprimer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winBank: public Ui_winBank {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINBANK_H
