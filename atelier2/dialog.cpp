#include "dialog.h"
#include "ui_dialog.h"

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





void Dialog::setathlete(athlete c){
    ui->lineedit_prenom2->setText(c.get_prenom());
    ui->lineedit_nom2->setText(c.get_nom());
    ui->lineedit_tel2->setText(c.get_tel());
    ui->lineedit_adresse2->setText(c.get_adresse());
    ui->lineedit_date->setText(c.get_date_as_string());
    //ui->lineedit_date->setdate(c.get_date());
    //ui->lineedit_date->setText(c.get_date_as_string());



    QString genre = c.get_genre();
        if (genre == "Homme") {
            ui->lineedit_genre2->setText("Homme");
        } else if (genre == "Femme") {
            ui->lineedit_genre2->setText("Femme");
        }
    QString TS= c.get_type_sport();
    ui->lineedit_typesport->setText(TS);

}





