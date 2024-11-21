#include "header/winAbout.h"
#include "ui_winabout.h"
#include "header/version.h"  // Inclusion du fichier version.h / Including version.h

WinAbout::WinAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinAbout)
{
    ui->setupUi(this);

    // Construire la chaîne de version en utilisant les macros définies dans version.h
    // Build the version string using the macros defined in version.h
    QString version = QString("Version : %1%2.%3.%4.%5")
                          .arg(VERSION_STATE)
                          .arg(RELEASE_MAJOR)
                          .arg(RELEASE_MINOR)
                          .arg(RELEASE_CODE)
                          .arg(BUILD_NUMBER);

    // Afficher la version dans le label labelVersion / Display the version in the label labelVersion
    ui->labelVersion->setText(version);

    // Désactiver le redimensionnement de la fenêtre / Disable window resizing
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->size());

    // Connecter le bouton "Ok" à la méthode accept(), qui ferme la fenêtre / Connect the "Ok" button to accept(), which closes the dialog
    connect(ui->pushButton, &QPushButton::clicked, this, &WinAbout::accept);
}

WinAbout::~WinAbout()
{
    delete ui;
}
