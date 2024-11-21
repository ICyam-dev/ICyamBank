/********************************************************************************
** Form generated from reading UI file 'winDoc.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOC_H
#define UI_WINDOC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_winDoc
{
public:
    QLabel *labelPicture;
    QLabel *labelNameDoc;
    QLabel *labelDesc;
    QLabel *labelTitle;
    QFrame *line;
    QLineEdit *lineEditNameDoc;
    QTextEdit *textEditDescDoc;
    QPushButton *pushBtnOk;

    void setupUi(QDialog *winDoc)
    {
        if (winDoc->objectName().isEmpty())
            winDoc->setObjectName("winDoc");
        winDoc->resize(411, 196);
        labelPicture = new QLabel(winDoc);
        labelPicture->setObjectName("labelPicture");
        labelPicture->setGeometry(QRect(10, 10, 64, 64));
        labelPicture->setPixmap(QPixmap(QString::fromUtf8(":/winPictures/doc_64.png")));
        labelNameDoc = new QLabel(winDoc);
        labelNameDoc->setObjectName("labelNameDoc");
        labelNameDoc->setGeometry(QRect(80, 80, 58, 16));
        labelDesc = new QLabel(winDoc);
        labelDesc->setObjectName("labelDesc");
        labelDesc->setGeometry(QRect(80, 110, 81, 16));
        labelTitle = new QLabel(winDoc);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(80, 10, 321, 41));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        line = new QFrame(winDoc);
        line->setObjectName("line");
        line->setGeometry(QRect(80, 50, 321, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        lineEditNameDoc = new QLineEdit(winDoc);
        lineEditNameDoc->setObjectName("lineEditNameDoc");
        lineEditNameDoc->setGeometry(QRect(170, 80, 231, 21));
        textEditDescDoc = new QTextEdit(winDoc);
        textEditDescDoc->setObjectName("textEditDescDoc");
        textEditDescDoc->setGeometry(QRect(170, 110, 231, 41));
        pushBtnOk = new QPushButton(winDoc);
        pushBtnOk->setObjectName("pushBtnOk");
        pushBtnOk->setGeometry(QRect(300, 160, 100, 32));

        retranslateUi(winDoc);

        QMetaObject::connectSlotsByName(winDoc);
    } // setupUi

    void retranslateUi(QDialog *winDoc)
    {
        winDoc->setWindowTitle(QCoreApplication::translate("winDoc", "D\303\251tail du document", nullptr));
        labelPicture->setText(QString());
        labelNameDoc->setText(QCoreApplication::translate("winDoc", "Nom :", nullptr));
        labelDesc->setText(QCoreApplication::translate("winDoc", "Description :", nullptr));
        labelTitle->setText(QCoreApplication::translate("winDoc", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:700;\">D\303\251tail du document</span></p></body></html>", nullptr));
        pushBtnOk->setText(QCoreApplication::translate("winDoc", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class winDoc: public Ui_winDoc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOC_H
