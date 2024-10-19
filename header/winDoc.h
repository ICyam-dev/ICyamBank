#ifndef WINDOC_H
#define WINDOC_H

#include <QDialog>
#include <QCloseEvent>   // Inclusion pour gérer l'événement de fermeture / Inclusion to handle the close event

namespace Ui {
class winDoc;
}

class winDoc : public QDialog
{
    Q_OBJECT

public:
    explicit winDoc(QWidget *parent = nullptr);
    ~winDoc();

    // Accesseurs pour les champs de texte / Accessors for text fields
    QString getDocName() const;          // Retourner le nom du document / Return document name
    QString getDocDescription() const;   // Retourner la description du document / Return document description

protected:
    void closeEvent(QCloseEvent *event) override;  // Empêcher la fermeture avec les boutons de contrôle / Prevent closing with control buttons

private:
    Ui::winDoc *ui;

private slots:
    void on_pushBtnOk_clicked();  // Slot pour gérer le clic sur le bouton "Ok" / Slot to handle the "Ok" button click
};

#endif // WINDOC_H
