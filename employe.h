#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDate>
#include <QDateEdit>

class employe
{
public:
    void setMatricule(QString matricule);
    void setPrenom(QString n);
    void setNom(QString n);
    void setNumeroTelephone(QString n);
    void setGenre(QString n);
    void setDateEmbauche(QDateEdit* dateEdit);
    void setAdresse(QString n);
    void setDateNaissance(QDateEdit* dateEdit);
    void setPoste(QString n);

    QString getMatricule();
    QString getPrenom();
    QString getNom();
    QString getNumeroTelephone();
    QString getGenre();
    QDate getDateEmbauche();
    QString getAdresse();
    QDate getDateNaissance();
    QString getPoste();

    QString getDateNaissanceAsString();

    employe();

private:
    QString matricule;
    QString prenom;
    QString nom;
    QString numeroTelephone;
    QString genre;
    QDate dateEmbauche;
    QString adresse;
    QDate dateNaissance;
    QString poste;
};

#endif // EMPLOYE_H
