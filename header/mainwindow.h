#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header/winabout.h"  // Inclusion de la fenêtre WinAbout / Including the WinAbout window
#include "header/winBank.h"   // Inclusion de la classe WinBank / Including the WinBank class

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);  // Constructeur de MainWindow / Constructor for MainWindow
    ~MainWindow();  // Destructeur de MainWindow / Destructor for MainWindow

private slots:
    void on_actionAbout_triggered();  // Slot pour gérer l'ouverture de la fenêtre "À propos" / Slot to handle the opening of the "About" window
    void on_actionBank_triggered();   // Slot pour gérer l'action du menu 'Bank' / Slot to handle the 'Bank' menu action
    void on_actionAccount_triggered();  // Slot pour gérer l'action du menu 'Account' / Slot to handle the 'Account' menu action
    void on_actionGroup_triggered();  // Slot pour gérer l'action du menu 'Group' / Slot to handle the 'Group' menu action

private:
    Ui::MainWindow *ui;  // Pointeur vers l'interface utilisateur / Pointer to the user interface
};

#endif // MAINWINDOW_H
