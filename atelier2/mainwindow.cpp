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
    ui->listWidget_photos->setIconSize(QSize(100, 100));
    cheminPhoto = "";
    chargerPhotosDepuisFichier();
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
    connect(ui->listWidget_photos, &QListWidget::itemClicked, this, &MainWindow::onPhotoClicked);

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

void MainWindow::chargerPhotosDepuisFichier()
{
    QFile file("chemin_photos.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Erreur lors de l'ouverture du fichier de chemins de photos!";
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 2) {
                QString idAthlete = parts[0];
                QString cheminPhoto = parts[1];

                // Charger la photo à partir du chemin
                QPixmap photo(cheminPhoto);
                if (!photo.isNull()) {
                    // Redimensionner la photo pour avoir la même taille
                    QSize desiredSize(200, 200); // Spécifiez la taille désirée ici
                    photo = photo.scaled(desiredSize, Qt::KeepAspectRatio);

                    // Créer un élément QListWidgetItem avec l'ID de l'athlète en tant que données utilisateur
                    QListWidgetItem *item = new QListWidgetItem();
                    item->setData(Qt::UserRole, idAthlete);
                    item->setIcon(QIcon(photo));

                    // Ajouter l'élément à la liste des photos
                    ui->listWidget_photos->addItem(item);
                } else {
                    qDebug() << "Impossible de charger la photo à partir du chemin : " << cheminPhoto;
                }
            }
        }

        file.close();
}


/*void MainWindow::ajouterPhotoDansListe(const QString &idAthlete, const QPixmap &photo)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setIcon(QIcon(photo));
    item->setData(Qt::UserRole, idAthlete); // Stocker l'ID de l'athlète comme données utilisateur de l'élément
    ui->listWidget_photos->addItem(item);
}*/


void MainWindow::onPhotoClicked(QListWidgetItem *item)
{
    QString idAthlete = item->data(Qt::UserRole).toString();
    afficherInformationsAthlete(idAthlete);
}


void MainWindow::afficherInformationsAthlete(const QString &idAthlete)
{
    // Recherche de l'athlète dans la base de données ou dans une structure de données appropriée
    athlete *a = rechercherParId(idAthlete.toInt());

    if (a != nullptr) {
        // Créer un modèle de données pour les informations de l'athlète
        QStandardItemModel *model = new QStandardItemModel(1, 5);

        // Insérer les données de l'athlète dans le modèle
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nom")));
        model->setItem(0, 0, new QStandardItem(a->get_nom()));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Prénom")));
        model->setItem(0, 1, new QStandardItem(a->get_prenom()));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Date de naissance")));
        model->setItem(0, 2, new QStandardItem(a->get_date_as_string()));
        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Genre")));
        model->setItem(0, 3, new QStandardItem(a->get_genre()));
        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type de sport")));
        model->setItem(0, 4, new QStandardItem(a->get_type_sport()));

        // Afficher le modèle dans le QTableView
        ui->tableView->setModel(model);

        // Libérer la mémoire une fois que vous avez fini d'utiliser l'objet
        delete a;
    } else {
        // Gérer le cas où l'athlète n'est pas trouvé
        QMessageBox::warning(this, "Avertissement", "Athlète non trouvé!", QMessageBox::Ok);
    }
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

/*void MainWindow::on_pushButton_choisirPhoto_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir une photo"), QDir::homePath(), tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!fileName.isEmpty()) {
        QPixmap photo(fileName);
        if (!photo.isNull()) {
            ui->label_photo->setPixmap(photo.scaled(ui->label_photo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // Enregistrer le chemin de la photo
            cheminPhoto = fileName;
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger l'image sélectionnée."));
        }
    }
}
*/
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
        QMessageBox::information(this, "Message", "Veuillez choisir votre photo faciale.", QMessageBox::Ok);
        //int idNouvelAthlete;
        int idNouvelAthlete;
        int idAthlete = a.getLastInsertedId(idNouvelAthlete);

                if (idAthlete > 0) {
                    // Sélectionner une photo
                    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choisir une photo"), "", tr("Images (*.png *.jpg *.jpeg)"));

                    // Vérifier si une photo a été sélectionnée
                    if (!imagePath.isEmpty()) {
                        // Enregistrer le chemin de la photo avec l'ID de l'athlète dans un fichier texte
                        if (enregistrerCheminPhoto(idAthlete, imagePath)) {
                            QMessageBox::information(this, "Message", "Chemin de la photo enregistré avec succès!", QMessageBox::Ok);
                        } else {
                            QMessageBox::warning(this, "Avertissement", "Erreur lors de l'enregistrement du chemin de la photo!", QMessageBox::Ok);
                        }
                    }
                } else {
                    QMessageBox::warning(this, "Avertissement", "Impossible de récupérer l'ID de l'athlète!", QMessageBox::Ok);
                }
            }
    }

// Fonction pour enregistrer le chemin de la photo avec l'ID de l'athlète dans un fichier texte
bool MainWindow::enregistrerCheminPhoto(int idAthlete, const QString& cheminPhoto)
{
    QFile file("chemin_photos.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier de chemin de photos!";
        return false;
    }

    QTextStream out(&file);
    out << idAthlete << "," << cheminPhoto << endl;
    file.close();
    return true;
}


QString MainWindow::getCheminPhoto(int idAthlete) const
{
    QFile file("chemin_photos.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier de chemin de photos!";
        return "";
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 2 && parts[0].toInt() == idAthlete) {
            file.close();
            return parts[1];
        }
    }
    file.close();
    return "";
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
    //return query.exec();
    if (query.exec()) {
            // Supprimer l'entrée correspondante dans le fichier chemin_photos.txt
            if (supprimerCheminPhoto(id)) {
                QMessageBox::information(this, "Information", "Athlète supprimé avec succès et son chemin de photo également!", QMessageBox::Ok);
                return true;
            } else {
                QMessageBox::warning(this, "Avertissement", "Erreur lors de la suppression de l'athlète du fichier de chemin de photos!", QMessageBox::Ok);
                return false;
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression de l'athlète!", QMessageBox::Ok);
            return false;
        }
}

bool MainWindow::supprimerCheminPhoto(int idAthlete)
{
    QString tempFileName = "chemin_photos_temp.txt";
    QFile inputFile("chemin_photos.txt");
    QFile tempFile(tempFileName);

    if (!inputFile.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Erreur lors de l'ouverture des fichiers pour la suppression du chemin de photo!";
        return false;
    }

    QTextStream in(&inputFile);
    QTextStream out(&tempFile);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 2 && parts[0].toInt() != idAthlete) {
            out << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (!inputFile.remove() || !tempFile.rename("chemin_photos.txt")) {
        qDebug() << "Erreur lors de la suppression du chemin de photo!";
        return false;
    }

    return true;
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineedit_id_rech->text().toInt();

    if (supprimerAthleteParId(id)) {
        actualiserListePhotos();
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
void MainWindow::actualiserListePhotos()
{
    // Effacer la liste actuelle des photos dans QListWidget
    ui->listWidget_photos->clear();

    // Recharger la liste des photos à partir du fichier chemin_photos.txt
    chargerPhotosDepuisFichier();
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

