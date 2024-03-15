#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QMainWindow>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
    class ChartWindow;
}

class ChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();

    void displayChart(); // Méthode pour configurer et afficher la charte

private:
    Ui::ChartWindow *ui;
};

#endif // CHARTWINDOW_H
