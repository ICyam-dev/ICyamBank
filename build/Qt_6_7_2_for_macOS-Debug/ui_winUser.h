/********************************************************************************
** Form generated from reading UI file 'winUser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINUSER_H
#define UI_WINUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_winUser
{
public:
    QLabel *labelPicture;
    QLabel *labelTitle;
    QComboBox *comboBoxFolder;
    QFrame *line;
    QLabel *labelNameFolder;
    QLabel *labelDescFolder;
    QLineEdit *lineEditNameFolder;
    QTextEdit *textEditDescFolder;
    QPushButton *pushBtnOk;
    QPushButton *pushBtnCancel;

    void setupUi(QDialog *winUser)
    {
        if (winUser->objectName().isEmpty())
            winUser->setObjectName("winUser");
        winUser->resize(438, 213);
        labelPicture = new QLabel(winUser);
        labelPicture->setObjectName("labelPicture");
        labelPicture->setGeometry(QRect(10, 10, 64, 64));
        labelPicture->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/openFolder-64.png")));
        labelTitle = new QLabel(winUser);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(90, 10, 241, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        comboBoxFolder = new QComboBox(winUser);
        comboBoxFolder->setObjectName("comboBoxFolder");
        comboBoxFolder->setGeometry(QRect(86, 39, 341, 32));
        line = new QFrame(winUser);
        line->setObjectName("line");
        line->setGeometry(QRect(20, 70, 401, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        labelNameFolder = new QLabel(winUser);
        labelNameFolder->setObjectName("labelNameFolder");
        labelNameFolder->setGeometry(QRect(20, 90, 58, 16));
        labelDescFolder = new QLabel(winUser);
        labelDescFolder->setObjectName("labelDescFolder");
        labelDescFolder->setGeometry(QRect(20, 120, 58, 16));
        lineEditNameFolder = new QLineEdit(winUser);
        lineEditNameFolder->setObjectName("lineEditNameFolder");
        lineEditNameFolder->setGeometry(QRect(90, 90, 331, 21));
        textEditDescFolder = new QTextEdit(winUser);
        textEditDescFolder->setObjectName("textEditDescFolder");
        textEditDescFolder->setGeometry(QRect(90, 120, 331, 41));
        pushBtnOk = new QPushButton(winUser);
        pushBtnOk->setObjectName("pushBtnOk");
        pushBtnOk->setGeometry(QRect(320, 170, 100, 32));
        pushBtnCancel = new QPushButton(winUser);
        pushBtnCancel->setObjectName("pushBtnCancel");
        pushBtnCancel->setGeometry(QRect(210, 170, 100, 32));

        retranslateUi(winUser);

        QMetaObject::connectSlotsByName(winUser);
    } // setupUi

    void retranslateUi(QDialog *winUser)
    {
        winUser->setWindowTitle(QCoreApplication::translate("winUser", "Dossier Utilisateur", nullptr));
        labelPicture->setText(QString());
        labelTitle->setText(QCoreApplication::translate("winUser", "Dossiers Utilisateur", nullptr));
        labelNameFolder->setText(QCoreApplication::translate("winUser", "Nom :", nullptr));
        labelDescFolder->setText(QCoreApplication::translate("winUser", "Desc. :", nullptr));
        pushBtnOk->setText(QCoreApplication::translate("winUser", "Ok", nullptr));
        pushBtnCancel->setText(QCoreApplication::translate("winUser", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winUser: public Ui_winUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINUSER_H
