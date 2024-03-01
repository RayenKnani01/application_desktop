#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "evenement.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    // Déclaration de la fonction setevenement
    void setevenement(evenement e);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
