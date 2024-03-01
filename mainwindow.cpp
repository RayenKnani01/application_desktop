#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include "dialog.h"
#include <QMessageBox>

#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_pressed()
{
    close();
}

void MainWindow::on_pushButton_clicked()
{
    evenement e;

    if (ui->lineedit_duree->text().isEmpty() ||
            ui->lineedit_titre->text().isEmpty() ||
            ui->lineedit_adresse->text().isEmpty() ||
            ui->lineedit_nbreathlete->text().isEmpty() ||
            ui->lineedit_typedesport->currentText().isEmpty() ||
            ui->lineedit_dateevenement->date().toString().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Tous les champs sont obligatoires!", QMessageBox::Ok);
        return; // Arrêter l'exécution supplémentaire
    }

    e.settitre(ui->lineedit_titre->text());
    e.setduree(ui->lineedit_duree->text());
    e.setadresse(ui->lineedit_adresse->text());
    e.setnbrathletes(ui->lineedit_nbreathlete->text());
    e.settypedesport(ui->lineedit_typedesport->currentText());
    e.setdate(ui->line_edit_dateevenement->date());

    Dialog d;
    d.setevenement(e); // Utilisation de l'objet e dans la fenêtre de dialogue
    d.exec();
}

void MainWindow::on_ajouter_2_clicked()
{
   QString titre = ui->lineedit_titre_3->text();
   QString titre = ui->lineedit_titre_3->text();
   QString titre = ui->lineedit_titre_3->text();
   QString titre = ui->lineedit_titre_3->text();
   QString titre = ui->lineedit_titre_3->text();
   QString titre = ui->lineedit_titre_3->text();
   evenement e(titre,duree,adresse,nbreathlete,typedesport,dateevenement);
   bool test = e.Ajouter();
   if (test)
   { QMessageBox::information(nullptr,
                              QObject::tr("Succès"),
                              QObject::tr(successMessage.toUtf8().constData()),  // Convert QString to const char*
                              QMessageBox::Ok);

   } else
   {
       QMessageBox::warning(nullptr, QObject::tr("Échec"),
                                     QObject::tr("Ajout non effectué\n"
                                                 "Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);

   }
}


void MainWindow::on_modifier_clicked()
{
    evenement P;
    // Récupérer les valeurs existantes
    QString existingNom = P.getnom();
        QString existingMdp = P.getmotdepasse();
        QString existingPoste = P.getposte();
    // Récupérer les nouvelles valeurs
        QString newNom2 = ui->lnom_32->text();
        QString newMdp2 = ui->lmdp_32->text();
        QString newPoste2 = ui->lposte_32->text();
     P.setid(id2);
        P.setnom(newNom2);
        P.setmotdepasse(newMdp2);
     bool test = P.modifier();
     if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK");}
    else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modification failed.\nClick Cancel to exit."), QMessageBox::Cancel);
        }

}
void mainwindow::loadFullTableView()
{
    QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT titre, adresse,nbreathlete,typedesport,dateevenement  FROM evenement order by titre");

    ui->table->setModel(model);
}
