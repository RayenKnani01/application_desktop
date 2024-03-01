#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QString>
#include <QDate>
#include <QMainWindow>
#include  <QMessageBox>


class evenement
{
public:
    evenement();
    evenement (QString,QString,QString,QString,QString,QString,QDate);

    // Setters
    void settitre(QString n);
    void settypesport(const QString n);
    void setdate(QDate date);
    void setnbrathletes(QString n);
    void setadresse(QString n);
    void setduree(QString n); // Ajout de la fonction setDuree
    void settypedesport(QString n);

    // Getters
    QString get_titre();
    QString get_typesport();
    QDate get_date();
    QString get_nbrathletes();
    QString get_adresse();
    QString getduree(); // Déclaration de la fonction getDuree
    QString get_date_as_string();
bool Ajouter();
bool Modifier();
bool supprimer(QString);
QSqlQueryModel*affiche();

private:
    QString titre;
    QString typesport;
    QDate date;
    QString nbrathletes;
    QString adresse;
    QString duree; // Ajout de la variable Durée
};

#endif // EVENEMENT_H
