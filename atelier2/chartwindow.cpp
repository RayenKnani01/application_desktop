#include "chartwindow.h"
#include "ui_chartwindow.h"

ChartWindow::ChartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::displayChart()
{
    // Créez votre charte et configurez-la
    QChart *chart = new QChart();
    // Ajoutez des données à la charte...

    // Créez une vue pour afficher la charte
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajoutez la vue de la charte à la fenêtre principale
    setCentralWidget(chartView);
}
