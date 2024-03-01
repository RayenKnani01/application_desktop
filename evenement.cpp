#include "evenement.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

const QString DATE_FORMAT = "dd/MM/yyyy"; // Constante pour le format de date

evenement::evenement()

    : titre(""), typesport(""),date(QDate::currentDate()), nbrathletes(""), adresse(""), duree("") // Initialisation des membres dans la liste d'initialisation
{}
evenement::evenement(QString titre,QString typesport,QString nbrathletes , QString adresse, QString duree ,QString typedesport , QDate date)

{ this->titre=titre;
 this->typesport=typesport;
this->nbrathletes=nbrathletes;
this->adresse=adresse;
this->duree=duree;
this->date=date;

}
void evenement::settitre(QString n) { titre = n; }
void evenement::settypesport(const QString n) { typesport = n; }
void evenement::setnbrathletes(QString n) { nbrathletes = n; }
void evenement::setadresse(QString n) { adresse = n; }
void evenement::setdate(QDate d) { date = d; } // Utilisation d'un nom de paramètre différent pour éviter les conflits de noms
void evenement::setduree(QString n) { duree = n; }
void evenement::settypedesport(QString n) { typesport = n; }

QString evenement::get_titre() { return titre; }
QString evenement::get_typesport() { return typesport; }
QString evenement::get_nbrathletes() { return nbrathletes; }
QString evenement::get_adresse() { return adresse; }
QDate evenement::get_date() { return date; }
QString evenement::getduree() { return duree; }
QString evenement::get_date_as_string() { return date.toString(DATE_FORMAT); }

//ajouter
bool evenement::Ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO evenement(titre, typesport, nbrathletes, adresse, date, duree");
                  "VALUES (:titre, :typesport, :nbrathletes, :adresse, :date, :duree)");//les noms de tableau base donnees

    query.bindValue(":titre", titre);
    query.bindValue(":typesport", typesport);
    query.bindValue(":nbrathletes", nbrathletes);
    query.bindValue(":adresse", adresse);
    query.bindValue(":date", date);
    query.bindValue(":duree", duree);

    return query.exec();}

    //modifier
    bool evenement::Modifier()
    {
        QSqlQuery query;
            query.prepare("UPDATE evenement SET titre='"+ titre+"',typesport='"+typesport+"',nbrathletes='"+nbrathletes+"',adresse='"+adresse+"',date='"+date+"',duree='"+duree+"'where titre='"+titre+"'" );

            query.bindValue(":titre", titre);
            query.bindValue(":typesport",typesport);
            query.bindValue(":nbrathletes", nbrathletes);
            query.bindValue("adresse",adresse);
            query.bindValue("date",date);
            query.bindValue("duree",duree);

       return query.exec();

    }

    bool evenement::supprimer(QString titre)
    {
        QSqlQuery query;

            query.prepare("Delete from evenement where titre=:titre");
            query.bindValue(0, titre);
       return query.exec();
    }

    QSqlQueryModel* evenement::affiche()
    {
        QSqlQueryModel* modele = new QSqlQueryModel();


        modele->setQuery("SELECT titre ,typesport, nbrathletes, adresse,date, duree FROM evenement order by titre");

        return modele;
    }


