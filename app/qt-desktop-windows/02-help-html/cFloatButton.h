#pragma once

#include <QWidget>
#include "IconsFontAwesome4.h"

namespace Ui
{
    class cFloatButton;
}

class cFloatButton : public QWidget
{
    Q_OBJECT

public:
    explicit cFloatButton(const QString &_iconLabel, QWidget *parent = 0);
    ~cFloatButton();

protected:
    bool eventFilter(QObject *object, QEvent *event);

signals:
    void emitClicked();

private:
    Ui::cFloatButton *ui;
    QString m_iconLabel;
};
