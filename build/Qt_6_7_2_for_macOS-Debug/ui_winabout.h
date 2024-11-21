/********************************************************************************
** Form generated from reading UI file 'winabout.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINABOUT_H
#define UI_WINABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WinAbout
{
public:
    QLabel *pictureLogo;
    QLabel *labelTitle;
    QLabel *labelVersion;
    QPushButton *pushButton;

    void setupUi(QDialog *WinAbout)
    {
        if (WinAbout->objectName().isEmpty())
            WinAbout->setObjectName("WinAbout");
        WinAbout->resize(429, 119);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WinAbout->sizePolicy().hasHeightForWidth());
        WinAbout->setSizePolicy(sizePolicy);
        WinAbout->setModal(true);
        pictureLogo = new QLabel(WinAbout);
        pictureLogo->setObjectName("pictureLogo");
        pictureLogo->setGeometry(QRect(20, 20, 64, 64));
        pictureLogo->setText(QString::fromUtf8(""));
        pictureLogo->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/Icone_ICyamBank-64.png")));
        labelTitle = new QLabel(WinAbout);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(100, 20, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        font.setBold(true);
        labelTitle->setFont(font);
        labelVersion = new QLabel(WinAbout);
        labelVersion->setObjectName("labelVersion");
        labelVersion->setGeometry(QRect(100, 50, 291, 20));
        pushButton = new QPushButton(WinAbout);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 80, 100, 32));

        retranslateUi(WinAbout);

        QMetaObject::connectSlotsByName(WinAbout);
    } // setupUi

    void retranslateUi(QDialog *WinAbout)
    {
        WinAbout->setWindowTitle(QCoreApplication::translate("WinAbout", "A propos de...", nullptr));
        labelTitle->setText(QCoreApplication::translate("WinAbout", "ICyamBank", nullptr));
        labelVersion->setText(QString());
        pushButton->setText(QCoreApplication::translate("WinAbout", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinAbout: public Ui_WinAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINABOUT_H
