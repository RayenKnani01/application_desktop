#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "athlete.h"


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
    void on_pushButton_3_pressed();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_rechercher2_clicked();
    void on_pushButton_modifier_clicked();
   // void slotComboBoxChanged();
private:
    Ui::MainWindow *ui;
    void rechercherAthleteParId(int id);
    void rechercherAthleteParId_modifier(int id);
    bool supprimerAthleteParId(int id);
    bool modifierAthlete(int id);
    athlete* rechercherParId(int id);

};
#endif // MAINWINDOW_H
