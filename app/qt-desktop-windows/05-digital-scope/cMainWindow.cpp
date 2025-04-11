#include "cMainWindow.h"
#include "ui_cMainWindow.h"
#include <QColorDialog>
#include <QResizeEvent>
#include <QMessageBox>

static const int DEF_REFRESH_TIME = 100; // 100ms : 10 Hz

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cMainWindow),
      m_refreshTime(DEF_REFRESH_TIME)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pagePlot);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_refreshTimerId = startTimer(m_refreshTime);
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::addManagePlot(const sPlot &_plot)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int iCol = 0;

    QTableWidgetItem *oId = new QTableWidgetItem(QString("%1").arg(_plot.id));
    QTableWidgetItem *oX = new QTableWidgetItem(QString("%1").arg(_plot.x));
    QTableWidgetItem *oY = new QTableWidgetItem(QString("%1").arg(_plot.y));
    QTableWidgetItem *oWidth = new QTableWidgetItem(QString("%1").arg(_plot.width));
    QTableWidgetItem *oHeight = new QTableWidgetItem(QString("%1").arg(_plot.height));
    QTableWidgetItem *oDivision = new QTableWidgetItem(QString("%1").arg(_plot.nDivision));

    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, iCol++, oId);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, iCol++, oX);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, iCol++, oY);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, iCol++, oWidth);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, iCol++, oHeight);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, iCol++, oDivision);
}

void cMainWindow::updateManagePlot()
{
    if (ui->plot->getSize())
    {
        ui->tableWidget->setRowCount(0);

        for (const auto &oPlot : ui->plot->getPlots())
        {
            addManagePlot(oPlot);
        }
    }
}

void cMainWindow::on_actionChangeBackgroundColor_triggered()
{
    QColor oldColor = ui->plot->getBackgroundColor();
    QColor newColor = QColorDialog::getColor(oldColor, this, tr("Sélectionner une couleur"));
    if (!newColor.isValid())
    {
        qDebug() << "Aucune couleur n'a ete selectionne.";
        return;
    }
    if (newColor != oldColor)
    {
        ui->plot->setBackgroundColor(newColor);
    }
}

void cMainWindow::on_actionAddPlot_triggered()
{
    if (ui->plot->isMax())
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le nombre maximal d'oscilloscopes est atteint."));
        return;
    }

    ui->plot->addPlot();
    updateManagePlot();
}

void cMainWindow::on_actionPlotPage_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePlot);
}

void cMainWindow::on_actionManagePlotPage_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageManagePlot);
}

void cMainWindow::on_plot_emitResizePlot()
{
    updateManagePlot();
}

void cMainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget *oCurrentWidget = ui->stackedWidget->currentWidget();
    if (oCurrentWidget != ui->pagePlot)
    {
        ui->stackedWidget->setCurrentWidget(ui->pagePlot);
        ui->stackedWidget->setCurrentWidget(oCurrentWidget);
    }
}

void cMainWindow::timerEvent(QTimerEvent *event)
{
    ui->plot->render();
    ui->plot->repaint();
}
