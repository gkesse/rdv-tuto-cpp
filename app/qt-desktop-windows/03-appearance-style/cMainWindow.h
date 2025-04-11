#pragma once

#include <QMainWindow>
#include "cActions.h"

class QLabel;

namespace Ui
{
    class cMainWindow;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    using sAction = cActions::sAction;

public:
    explicit cMainWindow(QWidget *parent = 0);
    ~cMainWindow();

private slots:
    void on_actionHomePage_triggered();
    void on_actionThemePage_triggered();
    void onAction(const sAction &_action);

private:
    Ui::cMainWindow *ui;
    QLabel *m_themeStatus;
};
