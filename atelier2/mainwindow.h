#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "athlete.h"
#include <QtCharts>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_2_pressed();
    //void on_pushButton_3_pressed();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_rechercher2_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButtonRechercher_met_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_tri_asc_clicked();
    void on_pushButton_tri_desc_clicked();
    void on_pushButton_export_pdf_clicked();
    void on_comboBoxCritere_currentIndexChanged(const QString &critere);
    bool enregistrerCheminPhoto(int idAthlete, const QString& cheminPhoto);
    QString getCheminPhoto(int idAthlete) const;
    void chargerPhotosDepuisFichier();
    //void ajouterPhotoDansListe(const QString &idAthlete, const QPixmap &photo);
    void onPhotoClicked(QListWidgetItem *item);
    void afficherInformationsAthlete(const QString &idAthlete);
    bool supprimerCheminPhoto(int idAthlete);
    void actualiserListePhotos();
    //void on_pushButton_choisirPhoto_clicked();
    //void on_pushButton_chart_clicked();


   // void slotComboBoxChanged();
private:
    Ui::MainWindow *ui;
    QString cheminPhoto;
    void rechercherAthleteParId(int id);
    void rechercherAthleteParId_modifier(int id);
    bool supprimerAthleteParId(int id);
    bool modifierAthlete(int id);
    athlete* rechercherParId(int id);
    void tri_liste_asc();
    void tri_liste_desc();
    void exportToPdf(const QString &fileName);
    QtCharts::QChartView* stats(QString critere);
};
#endif // MAINWINDOW_H
