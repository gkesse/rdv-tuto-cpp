#pragma once

#include <QWidget>

namespace Ui
{
    class cPortAction;
}

class cPortAction : public QWidget
{
    Q_OBJECT

public:
    explicit cPortAction(const QString &_portName, QWidget *parent = 0);
    ~cPortAction();

private:
    void initActions();

private slots:
    void onSendMessage();

signals:
    void emitSendMessage(QAction *);

private:
    Ui::cPortAction *ui;
    QString m_portName;
};
