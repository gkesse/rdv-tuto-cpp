#pragma once

#include <QMainWindow>

class cHelpWindow;

namespace Ui
{
    class cMainWindow;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit cMainWindow(QWidget *parent = 0);
    ~cMainWindow();

private slots:
    void on_actionHelpApp_triggered();
    void on_actionAboutApp_triggered();
    void on_actionAboutQt_triggered();

private:
    Ui::cMainWindow *ui;
    cHelpWindow *m_helpWindow;
};
