/********************************************************************************
** Form generated from reading UI file 'winGroup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINGROUP_H
#define UI_WINGROUP_H

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

class Ui_winGroup
{
public:
    QLabel *labelPictureGroup;
    QLabel *labelTitleGroup;
    QComboBox *comboBox;
    QFrame *line;
    QLabel *labelNameGroup;
    QLabel *labelDescGroup;
    QLineEdit *lineEditNameGroup;
    QTextEdit *textEditDescGroup;
    QPushButton *pushBtnOK;
    QPushButton *pushBtnCancel;
    QPushButton *pushBtnSupp;

    void setupUi(QDialog *winGroup)
    {
        if (winGroup->objectName().isEmpty())
            winGroup->setObjectName("winGroup");
        winGroup->resize(372, 228);
        labelPictureGroup = new QLabel(winGroup);
        labelPictureGroup->setObjectName("labelPictureGroup");
        labelPictureGroup->setGeometry(QRect(10, 10, 64, 64));
        labelPictureGroup->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/group_64.png")));
        labelTitleGroup = new QLabel(winGroup);
        labelTitleGroup->setObjectName("labelTitleGroup");
        labelTitleGroup->setGeometry(QRect(90, 10, 281, 31));
        labelTitleGroup->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        comboBox = new QComboBox(winGroup);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(80, 39, 291, 32));
        line = new QFrame(winGroup);
        line->setObjectName("line");
        line->setGeometry(QRect(90, 63, 271, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        labelNameGroup = new QLabel(winGroup);
        labelNameGroup->setObjectName("labelNameGroup");
        labelNameGroup->setGeometry(QRect(90, 80, 191, 16));
        labelDescGroup = new QLabel(winGroup);
        labelDescGroup->setObjectName("labelDescGroup");
        labelDescGroup->setGeometry(QRect(90, 130, 191, 16));
        lineEditNameGroup = new QLineEdit(winGroup);
        lineEditNameGroup->setObjectName("lineEditNameGroup");
        lineEditNameGroup->setGeometry(QRect(86, 100, 270, 21));
        textEditDescGroup = new QTextEdit(winGroup);
        textEditDescGroup->setObjectName("textEditDescGroup");
        textEditDescGroup->setGeometry(QRect(87, 150, 271, 41));
        pushBtnOK = new QPushButton(winGroup);
        pushBtnOK->setObjectName("pushBtnOK");
        pushBtnOK->setGeometry(QRect(296, 190, 61, 32));
        pushBtnCancel = new QPushButton(winGroup);
        pushBtnCancel->setObjectName("pushBtnCancel");
        pushBtnCancel->setGeometry(QRect(230, 190, 61, 32));
        pushBtnSupp = new QPushButton(winGroup);
        pushBtnSupp->setObjectName("pushBtnSupp");
        pushBtnSupp->setGeometry(QRect(87, 190, 61, 32));

        retranslateUi(winGroup);

        QMetaObject::connectSlotsByName(winGroup);
    } // setupUi

    void retranslateUi(QDialog *winGroup)
    {
        winGroup->setWindowTitle(QCoreApplication::translate("winGroup", "Les Groupes de compte", nullptr));
        labelPictureGroup->setText(QString());
        labelTitleGroup->setText(QCoreApplication::translate("winGroup", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:700;\">Les Groupes de compte</span></p></body></html>", nullptr));
        labelNameGroup->setText(QCoreApplication::translate("winGroup", "Nom du groupe :", nullptr));
        labelDescGroup->setText(QCoreApplication::translate("winGroup", "Courte description :", nullptr));
        pushBtnOK->setText(QCoreApplication::translate("winGroup", "Ok", nullptr));
        pushBtnCancel->setText(QCoreApplication::translate("winGroup", "Annuler", nullptr));
        pushBtnSupp->setText(QCoreApplication::translate("winGroup", "Supp.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winGroup: public Ui_winGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINGROUP_H
