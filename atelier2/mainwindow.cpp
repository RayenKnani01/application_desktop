#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "athlete.h"
#include "dialog.h"
#include <QMessageBox>
#include<QDate>
#include <QDebug>
#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QChartView>
#include <QtCharts/QPieSeries>
#include<QPieSlice>
#include<QChartView>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/img/logo_projet.png"));
    QPixmap pix(":/resources/img/logo_projet.png");
    /*int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));*/
    ui->lineedit_tel->setValidator(new QIntValidator(0, 99999999, this));
    connect(ui->pushButton_rechercher, SIGNAL(clicked()), this, SLOT(on_pushButton_rechercher_clicked()));
    connect(ui->pushButton_supprimer, SIGNAL(clicked()), this, SLOT(on_pushButton_supprimer_clicked()));
    connect(ui->pushButtonRechercher_met, SIGNAL(clicked()), this, SLOT(on_pushButtonRechercher_met_clicked()));
    connect(ui->pushButton_chart, SIGNAL(clicked()), this, SLOT(on_pushButton_chart_clicked()));
    // Validation for date of birth
        connect(ui->dateedit, &QDateEdit::dateChanged, [this]() {
            QDate date = ui->dateedit->date();
            QDate currentDate = QDate::currentDate();

            // Validate the date of birth
            if (date > currentDate) {
                QMessageBox::warning(this, "Avertissement", "La date de naissance ne peut pas être supérieure à la date actuelle!", QMessageBox::Ok);
                ui->dateedit->setDate(currentDate); // Reset the date of birth to current date
            }
        });

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*void MainWindow::on_pushButton_chart_clicked()
{
    // Créer une nouvelle scène graphique
    QGraphicsScene *scene = new QGraphicsScene();

    // Créer une série de données pour le graphique (par exemple, un graphique à secteurs)
    QPieSeries *series = new QPieSeries();

    // Vérifier le critère sélectionné dans le ComboBox
    QString critere = ui->combobox_chart->currentText();

    if (critere == "Genre") {
        // Récupérer les données de la base de données pour calculer les pourcentages
        int totalHommes = 0;
        int totalFemmes = 0;

        // Interroger la base de données pour récupérer les données pertinentes
        // Remplacez les requêtes fictives par les requêtes réelles pour récupérer les données de la base de données
        QSqlQuery queryHommes("SELECT COUNT(*) FROM ATHLETE WHERE GENRE = 'Homme'");
        if (queryHommes.next()) {
            totalHommes = queryHommes.value(0).toInt();
        }

        QSqlQuery queryFemmes("SELECT COUNT(*) FROM ATHLETE WHERE GENRE = 'Femme'");
        if (queryFemmes.next()) {
            totalFemmes = queryFemmes.value(0).toInt();
        }

        // Calculer les pourcentages
        int total = totalHommes + totalFemmes;
        if (total > 0) {
            double pourcentageHommes = (static_cast<double>(totalHommes) / total) * 100;
            double pourcentageFemmes = (static_cast<double>(totalFemmes) / total) * 100;

            // Ajouter les données au graphique
            series->append("Hommes", pourcentageHommes);
            series->append("Femmes", pourcentageFemmes);
        }
    } else if (critere == "Type de sport") {
        // Ajoutez votre logique pour récupérer les données et calculer les pourcentages en fonction du type de sport
    } else if (critere == "Date de naissance") {
        // Ajoutez votre logique pour récupérer les données et calculer les pourcentages en fonction de la date de naissance
    }

    // Ajouter la série à la scène
    scene->addItem(series);

    // Créer une vue pour afficher la scène graphique
    QGraphicsView *view = new QGraphicsView(scene);

    // Afficher la vue dans l'objet GraphicsView de votre interface MainWindow
    ui->graphicsView_chart->setScene(scene);
}

*/


void MainWindow::on_pushButton_2_pressed()
{
    close();
}

QSqlQueryModel* rechercher(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;


    query.prepare("SELECT * FROM ATHLETE WHERE ID_ATHLETE=:critere OR NOM = :critere OR PRENOM = :critere OR TYPE_SPORT = :critere");
    query.bindValue(":critere", critere);

    if (query.exec()) {
        model->setQuery(query);
        return model;
    } else {

        delete model;
        return nullptr;
    }
}




void MainWindow::on_pushButtonRechercher_met_clicked() {
    QString critereRecherche = ui->lineEdit_critereRecherche->text();
    QString typeRecherche = ui->comboBox_critereRecherche->currentText();

    athlete athleteInstance;

        // Appel de la fonction de recherche avec le critère et le type de recherche
        QSqlQueryModel* model = athleteInstance.rechercher(critereRecherche, typeRecherche);
    if (model != nullptr) {
        ui->tableView->setModel(model);
    } else {
        // Gérer les erreurs ou afficher un message à l'utilisateur selon vos besoins
        QMessageBox::warning(this, "Avertissement", "Erreur lors de la recherche!", QMessageBox::Ok);
    }
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
    if (!ui->lineedit_nom->text().contains(QRegExp("^[a-zA-Zéèêëàâäôöûüç -]+$")) ||
            !ui->lineedit_prenom->text().contains(QRegExp("^[a-zA-Zéèêëàâäôöûüç -]+$"))) {
            QMessageBox::critical(this, "Erreur", "Le nom et le prénom ne doivent contenir que des lettres alphabétiques!", QMessageBox::Ok);
            return; // Arrêter l'exécution ultérieure
        }
    if(ui->lineedit_tel->text().length()!=8)
    {
        QMessageBox::critical(this, "Error", "le numero de telephone est invalide!", QMessageBox::Ok);
        return;
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
           // Afficher les informations de l'athlète dans lxes lineEdits
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

           delete a;
       } else {
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

        if (ui->lineedit_prenom_modif->text().isEmpty() ||
                    ui->lineedit_nom_modif->text().isEmpty() ||
                    ui->lineedit_tel_modif->text().isEmpty() ||
                    ui->lineedit_adresse_modif->text().isEmpty() ||
                    (!ui->radiobutton_homme_modif->isChecked() && !ui->radiobutton_femme_modif->isChecked())) {
                    QMessageBox::critical(this, "Erreur", "Tous les champs obligatoires doivent être remplis!", QMessageBox::Ok);
                    delete a; // Assurez-vous de libérer la mémoire une fois que vous avez fini d'utiliser l'objet
                    return false; // Arrêter l'exécution ultérieure
                }

                if (!ui->lineedit_nom_modif->text().contains(QRegExp("^[a-zA-Zéèêëàâäôöûüç -]+$")) ||
                    !ui->lineedit_prenom_modif->text().contains(QRegExp("^[a-zA-Zéèêëàâäôöûüç -]+$"))) {
                    QMessageBox::critical(this, "Erreur", "Le nom et le prénom ne doivent contenir que des lettres alphabétiques!", QMessageBox::Ok);
                    delete a;
                    return false;
                }


                if (!ui->lineedit_tel_modif->text().contains(QRegExp("^[0-9]+$"))) {
                            QMessageBox::critical(this, "Erreur", "Le numéro de téléphone ne doit contenir que des chiffres!", QMessageBox::Ok);
                            delete a;
                            return false;
                        }
                if(ui->lineedit_tel->text().length()!=8)
                {
                    QMessageBox::critical(this, "Error", "le numero de telephone est invalide!", QMessageBox::Ok);
                    return false;
                }


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

        delete a;
        return success;
    } else {
        QMessageBox::warning(this, "Avertissement", "Athlète non trouvé!", QMessageBox::Ok);
        return false;
    }
}


void MainWindow::on_pushButton_modifier_clicked()
{
    int id = ui->lineedit_id_modif->text().toInt();
    modifierAthlete(id);
}


void MainWindow::on_pushButton_afficher_clicked()
{
    athlete a;

    // Afficher la liste des athlètes dans le QTableView
    QSqlQueryModel* model = a.afficher();

    if (model != nullptr) {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    }
}


void MainWindow::on_pushButton_tri_asc_clicked()
{
    QString critere = ui->comboBox_critereRech_2->currentText(); // Récupérer le critère de tri sélectionné

    QString query = "SELECT * FROM ATHLETE ORDER BY " + critere + " ASC"; // Construction de la requête SQL

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors du tri de la liste des athlètes : " << model->lastError().text();
        delete model;
        return;
    }

    // Mettre à jour le modèle du QTableView avec les données triées
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

void MainWindow::on_pushButton_tri_desc_clicked()
{
    QString critere = ui->comboBox_critereRech_2->currentText(); // Récupérer le critère de tri sélectionné

    QString query = "SELECT * FROM ATHLETE ORDER BY " + critere + " DESC"; // Construction de la requête SQL

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors du tri de la liste des athlètes : " << model->lastError().text();
        delete model;
        return;
    }

    // Mettre à jour le modèle du QTableView avec les données triées
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

void MainWindow::exportToPdf(const QString &fileName)
{
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer sous"), fileName, tr("Fichiers PDF (*.pdf)"));
    if (filePath.isEmpty()) return;

    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    ui->tableView->render(&painter);
}

void MainWindow::on_pushButton_export_pdf_clicked()
{
    exportToPdf("liste_athletes.pdf");
}





QtCharts::QChartView* MainWindow::stats(QString critere)
{
    QSqlQuery query;
    QString queryStr;

    if (critere == "TYPE_SPORT") {
        queryStr = "SELECT COUNT(*) as sportCount FROM ATHLETE GROUP BY TYPE_SPORT ORDER BY sportCount DESC";
    } else if (critere == "GENRE") {
        queryStr = "SELECT COUNT(*) as genreCount FROM ATHLETE GROUP BY GENRE ORDER BY genreCount DESC";
    } else if (critere == "DATE_NAISSANCE") {
        queryStr = "SELECT COUNT(*) as dateCount FROM ATHLETE GROUP BY DATE_NAISSANCE ORDER BY dateCount DESC";
    }

    query.exec(queryStr);

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    while (query.next()) {
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(category, count);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des données");

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}
void MainWindow::on_comboBoxCritere_currentIndexChanged(const QString &critere)
{
    QtCharts::QChartView *chartView = stats(critere);

        QGraphicsScene *scene = new QGraphicsScene();

        // Créer un QGraphicsProxyWidget pour encapsuler le QtCharts::QChartView
        QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
        proxy->setWidget(chartView);

        scene->addItem(proxy);

        ui->graphicsView_chart->setScene(scene);

}

