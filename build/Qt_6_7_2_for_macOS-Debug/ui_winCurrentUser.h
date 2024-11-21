/********************************************************************************
** Form generated from reading UI file 'winCurrentUser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINCURRENTUSER_H
#define UI_WINCURRENTUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_winCurrentUser
{
public:
    QLabel *labelPicture;
    QLabel *labelTitle;
    QFrame *line;
    QLabel *labelName;
    QLabel *labelMail;
    QLabel *labelAdress;
    QLabel *labelPhone;
    QLabel *labelFirstName;
    QLineEdit *lineEditPhone;
    QLineEdit *lineEditMail;
    QLineEdit *lineEditAdr1;
    QLineEdit *lineEditFirstname;
    QLineEdit *lineEditName;
    QLineEdit *lineEditAdr2;
    QLineEdit *lineEditAdr3;
    QPushButton *pushBtnOk;
    QPushButton *pushBtnCancel;

    void setupUi(QDialog *winCurrentUser)
    {
        if (winCurrentUser->objectName().isEmpty())
            winCurrentUser->setObjectName("winCurrentUser");
        winCurrentUser->resize(400, 332);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        winCurrentUser->setFont(font);
        labelPicture = new QLabel(winCurrentUser);
        labelPicture->setObjectName("labelPicture");
        labelPicture->setGeometry(QRect(10, 10, 64, 64));
        labelPicture->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/user-64.png")));
        labelTitle = new QLabel(winCurrentUser);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(80, 10, 291, 61));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        line = new QFrame(winCurrentUser);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 80, 371, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        labelName = new QLabel(winCurrentUser);
        labelName->setObjectName("labelName");
        labelName->setGeometry(QRect(10, 100, 101, 16));
        labelMail = new QLabel(winCurrentUser);
        labelMail->setObjectName("labelMail");
        labelMail->setGeometry(QRect(10, 190, 101, 16));
        labelAdress = new QLabel(winCurrentUser);
        labelAdress->setObjectName("labelAdress");
        labelAdress->setGeometry(QRect(10, 220, 101, 16));
        labelPhone = new QLabel(winCurrentUser);
        labelPhone->setObjectName("labelPhone");
        labelPhone->setGeometry(QRect(10, 160, 101, 16));
        labelFirstName = new QLabel(winCurrentUser);
        labelFirstName->setObjectName("labelFirstName");
        labelFirstName->setGeometry(QRect(10, 130, 101, 16));
        lineEditPhone = new QLineEdit(winCurrentUser);
        lineEditPhone->setObjectName("lineEditPhone");
        lineEditPhone->setGeometry(QRect(110, 158, 271, 21));
        lineEditMail = new QLineEdit(winCurrentUser);
        lineEditMail->setObjectName("lineEditMail");
        lineEditMail->setGeometry(QRect(110, 190, 271, 21));
        lineEditAdr1 = new QLineEdit(winCurrentUser);
        lineEditAdr1->setObjectName("lineEditAdr1");
        lineEditAdr1->setGeometry(QRect(110, 220, 271, 21));
        lineEditFirstname = new QLineEdit(winCurrentUser);
        lineEditFirstname->setObjectName("lineEditFirstname");
        lineEditFirstname->setGeometry(QRect(110, 130, 271, 21));
        lineEditName = new QLineEdit(winCurrentUser);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(110, 100, 271, 21));
        lineEditAdr2 = new QLineEdit(winCurrentUser);
        lineEditAdr2->setObjectName("lineEditAdr2");
        lineEditAdr2->setGeometry(QRect(110, 240, 271, 21));
        lineEditAdr3 = new QLineEdit(winCurrentUser);
        lineEditAdr3->setObjectName("lineEditAdr3");
        lineEditAdr3->setGeometry(QRect(110, 260, 271, 21));
        pushBtnOk = new QPushButton(winCurrentUser);
        pushBtnOk->setObjectName("pushBtnOk");
        pushBtnOk->setGeometry(QRect(280, 290, 100, 32));
        pushBtnCancel = new QPushButton(winCurrentUser);
        pushBtnCancel->setObjectName("pushBtnCancel");
        pushBtnCancel->setGeometry(QRect(170, 290, 100, 32));
        QWidget::setTabOrder(lineEditName, lineEditFirstname);
        QWidget::setTabOrder(lineEditFirstname, lineEditPhone);
        QWidget::setTabOrder(lineEditPhone, lineEditMail);
        QWidget::setTabOrder(lineEditMail, lineEditAdr1);
        QWidget::setTabOrder(lineEditAdr1, lineEditAdr2);
        QWidget::setTabOrder(lineEditAdr2, lineEditAdr3);
        QWidget::setTabOrder(lineEditAdr3, pushBtnCancel);
        QWidget::setTabOrder(pushBtnCancel, pushBtnOk);

        retranslateUi(winCurrentUser);

        QMetaObject::connectSlotsByName(winCurrentUser);
    } // setupUi

    void retranslateUi(QDialog *winCurrentUser)
    {
        winCurrentUser->setWindowTitle(QCoreApplication::translate("winCurrentUser", "Utilisateur en cours", nullptr));
        labelPicture->setText(QString());
        labelTitle->setText(QCoreApplication::translate("winCurrentUser", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">Donn\303\251es Utilisateur</span></p><p>Ce formulaire pour vous saisir les donn\303\251es <br/>utlisateur pr\303\251sent sur vos rapports et vos \303\251tats.</p></body></html>", nullptr));
        labelName->setText(QCoreApplication::translate("winCurrentUser", "Nom :", nullptr));
        labelMail->setText(QCoreApplication::translate("winCurrentUser", "Courriel :", nullptr));
        labelAdress->setText(QCoreApplication::translate("winCurrentUser", "Adresse :", nullptr));
        labelPhone->setText(QCoreApplication::translate("winCurrentUser", "T\303\251l\303\251phone :", nullptr));
        labelFirstName->setText(QCoreApplication::translate("winCurrentUser", "Pr\303\251nom :", nullptr));
        pushBtnOk->setText(QCoreApplication::translate("winCurrentUser", "Ok", nullptr));
        pushBtnCancel->setText(QCoreApplication::translate("winCurrentUser", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winCurrentUser: public Ui_winCurrentUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINCURRENTUSER_H
