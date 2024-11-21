/********************************************************************************
** Form generated from reading UI file 'winInsertData.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WININSERTDATA_H
#define UI_WININSERTDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_winInsertData
{
public:
    QLabel *labelPicture;
    QLabel *labelTitle;
    QPushButton *BtnYes;
    QPushButton *BtnNo;

    void setupUi(QDialog *winInsertData)
    {
        if (winInsertData->objectName().isEmpty())
            winInsertData->setObjectName("winInsertData");
        winInsertData->resize(400, 106);
        labelPicture = new QLabel(winInsertData);
        labelPicture->setObjectName("labelPicture");
        labelPicture->setGeometry(QRect(10, 10, 64, 64));
        labelPicture->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/Icone_ICyamBank-64.png")));
        labelTitle = new QLabel(winInsertData);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(80, 10, 311, 64));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        BtnYes = new QPushButton(winInsertData);
        BtnYes->setObjectName("BtnYes");
        BtnYes->setGeometry(QRect(290, 70, 100, 32));
        BtnNo = new QPushButton(winInsertData);
        BtnNo->setObjectName("BtnNo");
        BtnNo->setGeometry(QRect(180, 70, 100, 32));

        retranslateUi(winInsertData);

        QMetaObject::connectSlotsByName(winInsertData);
    } // setupUi

    void retranslateUi(QDialog *winInsertData)
    {
        winInsertData->setWindowTitle(QCoreApplication::translate("winInsertData", "Dialog", nullptr));
        labelPicture->setText(QString());
        labelTitle->setText(QCoreApplication::translate("winInsertData", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:700;\">Ins\303\251rer des donn\303\251es d'exemple<br/></span><span style=\" font-size:14pt;\">Voulez-vous ins\303\251rer des donn\303\251es d'exemple <br/>dans le nouveau dossier ?</span><br/></p></body></html>", nullptr));
        BtnYes->setText(QCoreApplication::translate("winInsertData", "Oui", nullptr));
        BtnNo->setText(QCoreApplication::translate("winInsertData", "Non", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winInsertData: public Ui_winInsertData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WININSERTDATA_H
