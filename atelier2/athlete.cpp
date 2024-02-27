#include "athlete.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QString>
#include<QDate>
#include<QSqlError>

athlete::athlete()
{
 nom="";
 prenom="";
date=QDate::fromString( "dd/MM/yyyy");
tel="";
genre="";
type_sport="";
 adresse="";
}
athlete::athlete(QString nom, QString prenom, QString tel, QDate date, QString adresse, QString type_sport, QString genre) {
    // Initialisation des membres de la classe avec les valeurs passées en arguments
    this->nom = nom;
    this->prenom = prenom;
    this->tel = tel;
    this->date = date;
    this->adresse = adresse;
    this->type_sport = type_sport;
    this->genre = genre;
}
/*
athlete::athlete(QString nom,QString prenom,QString tel,QDate date,QString adresse,QString type_sport,QString genre){

    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
     this->date=date;
    this->adresse=adresse;
    this->type_sport=type_sport;
    this->genre=genre;
}
*/

void athlete::setprenom(QString n){prenom=n;}
void athlete::setnom(QString n){nom=n;}
void athlete::settel(QString n){tel=n;}
void athlete::setadresse(QString n){adresse=n;}
void athlete::setdate(QDateEdit* dateedit)
{
    date = dateedit->date();
}
void athlete::settype_genre(QString n){genre=n;}
//void athlete::setdate(QDate n){date=n;}
void athlete::settype_sport(QString n){type_sport=n;}

QString athlete::get_prenom(){return prenom;}
QString athlete::get_nom(){return nom;}
QString athlete::get_tel(){return tel;}
QString athlete::get_adresse(){return adresse;}
QDate athlete::get_date(){return date;}
QString athlete::get_type_sport(){return type_sport;}
QString athlete::get_genre(){return genre;}

QString athlete::get_date_as_string()
{
    QString date_fin;
    return date_fin=date.toString("dd/MM/yyyy");
}




    bool athlete::ajouter(){
        athlete c;
        QSqlQuery query;
        query.prepare("INSERT INTO ATHLETE(NOM, PRENOM, TEL, ADRESSE, TYPE_SPORT, GENRE ,DATE_NAISSANCE)"
                      "VALUES (:NOM, :PRENOM, :TEL, :ADRESSE, :TYPE_SPORT, :GENRE, :DATE_NAISSANCE)");
        query.bindValue(":NOM", nom);
        query.bindValue(":PRENOM", prenom);
        query.bindValue(":TEL", tel);
        query.bindValue(":ADRESSE", adresse);
        query.bindValue(":TYPE_SPORT", type_sport);
        query.bindValue(":GENRE", genre);
        query.bindValue(":DATE_NAISSANCE", date);
        // Ajoutez les valeurs manquantes ici.
        return query.exec();
    }

    bool athlete::supprimer(int id)
    {
        QSqlQuery query;
        QString id_string = QString::number(id);
        query.prepare("DELETE FROM ATHLETE WHERE ID_ATHLETE = :id");
        query.bindValue(":id", id);
        return query.exec();
    }
   athlete athlete::rechercherParId(int id)
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM ATHLETE WHERE ID_ATHLETE = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            // Récupérer les informations de l'athlète
            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            QDate date = query.value("DATE_NAISSANCE").toDate(); // Récupérer en tant que QDate
            QString adresse = query.value("ADRESSE").toString();
            QString genre = query.value("GENRE").toString();
            QString tel = query.value("TEL").toString();
            QString TS =  query.value("TYPE_SPORT").toString();
            // Ajoutez d'autres colonnes en fonction de votre schéma de base de données

            // Créer un nouvel objet athlete avec les informations récupérées
            return athlete(nom, prenom, tel, date, adresse, TS, genre);
        } else {
            // En cas d'erreur ou si l'athlète n'est pas trouvé, retourner nullptr ou gérer l'erreur selon vos besoins
            return athlete();
        }
    }


   bool athlete::modifier(int id)
   {
       QSqlQuery query;
       query.prepare("UPDATE ATHLETE SET NOM = :nom, PRENOM = :prenom, TEL = :tel, ADRESSE = :adresse, TYPE_SPORT = :type_sport, GENRE = :genre, DATE_NAISSANCE = :date WHERE ID_ATHLETE = :id");
       query.bindValue(":id", id);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":date", date);
       query.bindValue(":adresse", adresse);
       query.bindValue(":genre", genre);
       query.bindValue(":tel", tel);
       query.bindValue(":type_sport", type_sport);


       return query.exec();
   }




