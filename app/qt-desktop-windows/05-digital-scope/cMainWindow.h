#pragma once

#include <QMainWindow>
#include "cPlot.h"

namespace Ui
{
    class cMainWindow;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    using sPlot = cPlot::sPlot;
    using sPlots = cPlot::sPlots;

public:
    explicit cMainWindow(QWidget *parent = 0);
    ~cMainWindow();

private:
    void addManagePlot(const sPlot &_plot);
    void updateManagePlot();

private slots:
    void on_actionChangeBackgroundColor_triggered();
    void on_actionAddPlot_triggered();
    void on_actionPlotPage_triggered();
    void on_actionManagePlotPage_triggered();
    void on_plot_emitResizePlot();

protected:
    void resizeEvent(QResizeEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    Ui::cMainWindow *ui;
    QVector<QImage> m_images;
    int m_refreshTime;
    int m_refreshTimerId;
};
