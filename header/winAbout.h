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
    // Constructeur : initialise la fenêtre À propos / Constructor: initializes the About window
    explicit WinAbout(QWidget *parent = nullptr);

    // Destructeur : nettoie les ressources de la fenêtre / Destructor: cleans up window resources
    ~WinAbout();

private:
    Ui::WinAbout *ui;  // Interface utilisateur pour WinAbout / User interface for WinAbout
};

#endif // WINABOUT_H
