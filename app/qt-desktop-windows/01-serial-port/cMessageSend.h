#pragma once

#include <QWidget>

namespace Ui
{
    class cMessageSend;
}

class cMessageSend : public QWidget
{
    Q_OBJECT

public:
    explicit cMessageSend(const QString &_message, QWidget *parent = 0);
    ~cMessageSend();

private:
    Ui::cMessageSend *ui;
    QString m_message;
};
