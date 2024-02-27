#ifndef DIALOG_H
#define DIALOG_H
#include "athlete.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setathlete(athlete c);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
