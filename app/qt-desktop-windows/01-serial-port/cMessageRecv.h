#pragma once

#include <QWidget>

namespace Ui
{
    class cMessageRecv;
}

class cMessageRecv : public QWidget
{
    Q_OBJECT

public:
    explicit cMessageRecv(const QString &_message, QWidget *parent = 0);
    ~cMessageRecv();

private:
    Ui::cMessageRecv *ui;
    QString m_message;
};
