#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "athlete.h"
#include "dialog.h"
#include <QMessageBox>
#include<QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/rayen/Desktop/logo_projet.png");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ui->lineedit_tel->setValidator(new QIntValidator(0, 99999999, this));
    connect(ui->pushButton_rechercher, SIGNAL(clicked()), this, SLOT(on_pushButton_rechercher_clicked()));
    connect(ui->pushButton_supprimer, SIGNAL(clicked()), this, SLOT(on_pushButton_supprimer_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_pressed()
{
    close();
}

void MainWindow::on_pushButton_3_pressed()
{
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    athlete c;
    QString TS = ui->combobox->currentText();
    QString firstChoice = ui->combobox->itemText(0);

    if (ui->lineedit_prenom->text().isEmpty() ||
        ui->lineedit_nom->text().isEmpty() ||
        ui->lineedit_tel->text().isEmpty() ||
        ui->lineedit_adresse->text().isEmpty() ||
        (!ui->radiobutton_homme->isChecked() && !ui->radiobutton_femme->isChecked())) {
        QMessageBox::critical(this, "Error", "Tous les champs sont obligatoires!", QMessageBox::Ok);
        return; // Stop further execution
    }

    c.setprenom(ui->lineedit_prenom->text());
    c.setnom(ui->lineedit_nom->text());
    c.settel(ui->lineedit_tel->text());
    c.setadresse(ui->lineedit_adresse->text());
    c.setdate(ui->dateedit);
    QString genre;
    if (ui->radiobutton_homme->isChecked()) {
        genre = "Homme";
    } else if (ui->radiobutton_femme->isChecked()) {
        genre = "Femme";
    }

    // Affectation type de sport
    c.settype_genre(genre);
    c.settype_sport(TS);

    QString prenom = ui->lineedit_prenom->text();
    QString nom = ui->lineedit_nom->text();
    QString tel = ui->lineedit_tel->text();
    QString adresse = ui->lineedit_adresse->text();
    QDate date = ui->dateedit->date();

    athlete a(nom, prenom, tel, date, adresse, TS, genre);
    if (TS == firstChoice) {
        QMessageBox::critical(this, "Error", "Choisir un type de sport", QMessageBox::Ok);
        return; // Stop further execution
    } else if (a.ajouter()) {
        QMessageBox::information(this, "Message", "Athlète ajouté", QMessageBox::Ok);
    }
}


// Fonction pour rechercher un athlète par son ID
athlete* MainWindow::rechercherParId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ATHLETE WHERE ID_ATHLETE = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString nom = query.value("NOM").toString();
        QString prenom = query.value("PRENOM").toString();
        QDate date = query.value("DATE_NAISSANCE").toDate();
        QString adresse = query.value("ADRESSE").toString();
        QString genre = query.value("GENRE").toString();
        QString tel = query.value("TEL").toString();
        QString type_sport =  query.value("TYPE_SPORT").toString();


        // Créer un nouvel objet athlete avec les informations récupérées
        athlete* a = new athlete(nom, prenom, tel, date, adresse, type_sport, genre);
        return a;
    } else {
        // En cas d'erreur ou si l'athlète n'est pas trouvé, retourner nullptr ou gérer l'erreur selon vos besoins
        return nullptr;
    }
}
void MainWindow::rechercherAthleteParId(int id)
{
    athlete* a = rechercherParId(id);

    if (a != nullptr) {
        // Afficher les informations de l'athlète dans les lineEdits
        ui->lineedit_nom_supp->setText(a->get_nom());
        ui->lineedit_prenom_supp->setText(a->get_prenom());
        ui->lineedit_date_supp->setText(a->get_date_as_string());
        ui->lineedit_genre_supp->setText(a->get_genre());
        ui->lineedit_ts_supp->setText(a->get_type_sport());

        delete a; // Assurez-vous de libérer la mémoire une fois que vous avez fini d'utiliser l'objet
    } else {
        // Gérer le cas où l'athlète n'est pas trouvé
        QMessageBox::warning(this, "Avertissement", "Athlète non trouvé!", QMessageBox::Ok);
    }
}





void MainWindow::rechercherAthleteParId_modifier(int id)
{
    athlete* a = rechercherParId(id);

       if (a != nullptr) {
           // Afficher les informations de l'athlète dans les lineEdits
           ui->lineedit_nom_modif->setText(a->get_nom());
           ui->lineedit_prenom_modif->setText(a->get_prenom());
           ui->dateedit_modif->setDate(a->get_date());
           ui->lineedit_adresse_modif->setText(a->get_adresse());

           // Afficher le genre en tant que radio bouton
           if (a->get_genre() == "Homme") {
               ui->radiobutton_homme_modif->setChecked(true);
               ui->radiobutton_femme_modif->setChecked(false);
           } else if (a->get_genre() == "Femme") {
               ui->radiobutton_homme_modif->setChecked(false);
               ui->radiobutton_femme_modif->setChecked(true);
           }
            ui->lineedit_tel_modif->setText(a->get_tel());
           // Afficher le type de sport dans la combobox
           ui->combobox_modif->setCurrentText(a->get_type_sport());

           delete a; // Assurez-vous de libérer la mémoire une fois que vous avez fini d'utiliser l'objet
       } else {
           // Gérer le cas où l'athlète n'est pas trouvé
           QMessageBox::warning(this, "Avertissement", "Athlète non trouvé!", QMessageBox::Ok);
       }
}

void MainWindow::on_pushButton_rechercher_clicked()
{

    int id = ui->lineedit_id_rech->text().toInt();
    rechercherAthleteParId(id);
}

void MainWindow::on_pushButton_rechercher2_clicked()
{

    int id = ui->lineedit_id_modif->text().toInt();
    rechercherAthleteParId_modifier(id);
}

// Fonction pour supprimer un athlète par son ID
bool MainWindow::supprimerAthleteParId(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ATHLETE WHERE ID_ATHLETE = :id");
    query.bindValue(":id", id);

    return query.exec();
}



void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineedit_id_rech->text().toInt();

    if (supprimerAthleteParId(id)) {
        QMessageBox::information(this, "Information", "Athlète supprimé avec succès!", QMessageBox::Ok);
        ui->lineedit_nom_supp->clear();
        ui->lineedit_prenom_supp->clear();
        ui->lineedit_date_supp->clear();
        ui->lineedit_genre_supp->clear();
        ui->lineedit_ts_supp->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression de l'athlète!", QMessageBox::Ok);
    }
}


bool MainWindow::modifierAthlete(int id)
{
    athlete* a = rechercherParId(id);

    if (a != nullptr) {
        // Modifier les informations de l'athlète
        a->setnom(ui->lineedit_nom_modif->text());
        a->setprenom(ui->lineedit_prenom_modif->text());
        a->settel(ui->lineedit_tel_modif->text());
        a->setadresse(ui->lineedit_adresse_modif->text());
        a->setdate(ui->dateedit_modif);

        QString genre;
        if (ui->radiobutton_homme_modif->isChecked()) {
            genre = "Homme";
        } else if (ui->radiobutton_femme_modif->isChecked()) {
            genre = "Femme";
        }
        a->settype_genre(genre);

        QString TS = ui->combobox_modif->currentText();
        a->settype_sport(TS);

        // Appeler la méthode de modification
        bool success = a->modifier(id);

        if (success) {
            QMessageBox::information(this, "Information", "Informations de l'athlète modifiées avec succès!", QMessageBox::Ok);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification des informations de l'athlète!", QMessageBox::Ok);
        }

        delete a; // Assurez-vous de libérer la mémoire une fois que vous avez fini d'utiliser l'objet
        return success;
    } else {
        // Gérer le cas où l'athlète n'est pas trouvé
        QMessageBox::warning(this, "Avertissement", "Athlète non trouvé!", QMessageBox::Ok);
        return false;
    }
}


void MainWindow::on_pushButton_modifier_clicked()
{
    int id = ui->lineedit_id_modif->text().toInt();
    modifierAthlete(id);
}
