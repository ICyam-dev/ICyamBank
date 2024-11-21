#include "header/winDoc.h"
#include "ui_winDoc.h"

winDoc::winDoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winDoc)
{
    ui->setupUi(this);

    // Empêcher l'agrandissement et fixer la taille de la fenêtre / Prevent resizing and set the window size
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Désactiver le bouton de fermeture / Disable the close button
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);

    // Connexion du bouton "Ok" à la méthode accept() pour fermer la fenêtre / Connect the "Ok" button to accept() to close the window
    connect(ui->pushBtnOk, &QPushButton::clicked, this, &winDoc::on_pushBtnOk_clicked);
}

void winDoc::closeEvent(QCloseEvent *event)
{
    // Empêcher la fermeture de la fenêtre avec le bouton de contrôle / Prevent closing the window with control buttons
    event->ignore();
}

void winDoc::on_pushBtnOk_clicked()
{
    // Fermer la fenêtre quand le bouton "Ok" est cliqué / Close the window when "Ok" is clicked
    this->accept();
}

winDoc::~winDoc()
{
    delete ui;
}

// Accesseur pour le nom du document / Accessor for the document name
QString winDoc::getDocName() const {
    return ui->lineEditNameDoc->text();
}

// Accesseur pour la description du document / Accessor for the document description
QString winDoc::getDocDescription() const {
    return ui->textEditDescDoc->toPlainText();
}
