#ifndef ATHLETE_H
#define ATHLETE_H
#include <QString>
#include <QDateEdit>
#include<QSqlQuery>
#include<QSqlQueryModel>

class athlete
{

public:
    athlete();
    athlete(QString,QString,QString,QDate,QString,QString,QString);
    void setprenom(QString n);
    void setnom(QString n);
    void settel(QString n);
    void setadresse(QString n);
    void setdate(QDateEdit* dateEdit);
    void settype_sport(const QString n);
    void settype_genre(QString n);



    QString get_prenom();
    QString get_nom();
    QString get_tel();
    QString get_adresse();
    QDate get_date();
    QString get_type_sport();
    QString get_date_as_string();
    QString get_genre();
     void rechercherAthleteParId(int id);
    athlete rechercherParId(int id);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int id);


    QString prenom,nom,tel,adresse,type_sport,genre;
    QDate date;
};


#endif // ATHLETE_H
