#ifndef WINABOUT_H
#define WINABOUT_H

#include <QDialog>

namespace Ui {
class WinAbout;
}

class WinAbout : public QDialog
{
    Q_OBJECT

public:
    // Constructeur de la fenêtre WinAbout / Constructor for WinAbout window
    explicit WinAbout(QWidget *parent = nullptr);

    // Destructeur de la fenêtre WinAbout / Destructor for WinAbout window
    ~WinAbout();

private:
    Ui::WinAbout *ui;  // Interface utilisateur / User interface
};

#endif // WINABOUT_H
