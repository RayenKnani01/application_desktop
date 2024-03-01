#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLineEdit>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadFullTableView();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_pressed();
   // void slotComboBoxChanged();
    void on_ajouter_2_clicked();

    void on_lineedit_titre_3_cursorPositionChanged(int arg1, int arg2);

    void on_modifier_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H