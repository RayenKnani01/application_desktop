#include "employe.h"

employe::employe()
{
    matricule = "";
    numeroTelephone = "";
    prenom = "";
    nom = "";
    genre = "";
    adresse = "";
    poste = "";
}

void employe::setPrenom(QString n) { prenom = n; }
void employe::setNom(QString n) { nom = n; }
void employe::setNumeroTelephone(QString n) { numeroTelephone = n; }
void employe::setAdresse(QString n) { adresse = n; }
void employe::setDateNaissance(QDateEdit* dateedit)
{
    dateNaissance = dateedit->date();
}
void employe::setGenre(QString n) { genre = n; }
void employe::setDateEmbauche(QDateEdit* dateedit)
{
    dateEmbauche = dateedit->date();
}
void employe::setPoste(QString n) { poste = n; }

QString employe::getPrenom() { return prenom; }
QString employe::getNom() { return nom; }
QString employe::getNumeroTelephone() { return numeroTelephone; }
QString employe::getAdresse() { return adresse; }
QDate employe::getDateNaissance() { return dateNaissance; }
QString employe::getGenre() { return genre; }
QDate employe::getDateEmbauche() { return dateEmbauche; }
QString employe::getPoste() { return poste; }

QString employe::getDateNaissanceAsString()
{
    return dateNaissance.toString("dd/MM/yyyy");
}
