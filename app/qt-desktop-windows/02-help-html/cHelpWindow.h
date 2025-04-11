#pragma once

#include <QDialog>

class cFloatButton;

namespace Ui
{
    class cHelpWindow;
}

class cHelpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit cHelpWindow(const QString &_message, QWidget *parent = 0);
    ~cHelpWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onOpenTopLink();
    void onOpenBottomLink();

private:
    Ui::cHelpWindow *ui;
    QString m_message;
    cFloatButton *m_topLink;
    cFloatButton *m_bottomLink;
};
