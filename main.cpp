#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMainWindow window;
        window.setWindowTitle("Formulaire");

        QFormLayout formLayout(&window);

        QLineEdit *titreLineEdit = new QLineEdit(&window);
        QLineEdit *TypedesportLineEdit = new QLineEdit(&window);
        QLineEdit *Date_evennementLineEdit = new QLineEdit(&window);
        QLineEdit *DuréeLineEdit = new QLineEdit(&window);
        QLineEdit *adresseLineEdit = new QLineEdit(&window);
        QLineEdit *nbr_athletesLineEdit = new QLineEdit(&window);

        formLayout.addRow("Titre:", titreLineEdit);
        formLayout.addRow("Type de sport:", TypedesportLineEdit);
        formLayout.addRow("Date de l'événement:", Date_evennementLineEdit);
        formLayout.addRow("Durée:", DuréeLineEdit);
        formLayout.addRow("Adresse:", adresseLineEdit);
        formLayout.addRow("Nombre d'athlètes:", nbr_athletesLineEdit);

        QPushButton *afficherButton = new QPushButton("Afficher", &window);
        QLabel *infoLabel = new QLabel(&window);

        formLayout.addRow(afficherButton);
        formLayout.addRow(infoLabel);

        QObject::connect(afficherButton, &QPushButton::clicked, [&]() {
            QString titre = titreLineEdit->text();
            QString Typedesport = TypedesportLineEdit->text();
            QString Date_evennement = Date_evennementLineEdit->text();
            QString Durée = DuréeLineEdit->text();
            QString adresse = adresseLineEdit->text();
            QString nbr_athletes = nbr_athletesLineEdit->text();

            QString infoText = "Titre: " + titre + "\nType de sport: " + Typedesport + "\nDate de l'événement: " + Date_evennement + "\nDurée: " + Durée + "\nAdresse: " + adresse + "\nNombre d'athlètes: " + nbr_athletes;
            infoLabel->setText(infoText);
        });

        window.show();
        return app.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("La base de données n'est pas ouverte"),
                              QObject::tr("Échec de la connexion.\n"
                                          "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        return -1;
    }
}




