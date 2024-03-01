#include "dialog.h"
#include "ui_dialog.h"
#include "evenement.h"
#include <QDate>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setevenement(evenement e){

    ui->lineedit_duree->setText(e.getduree());
    ui->lineedit_titre->setText(e.get_titre());
    ui->lineedit_adresse->setText(e.get_adresse());
    ui->lineedit_nbreathlete->setText(e.get_nbrathletes());


    ui->lineedit_dateevenement->setDate(e.get_date());


    ui->lineedit_typedesport->setCurrentText(e.get_typesport());
}











