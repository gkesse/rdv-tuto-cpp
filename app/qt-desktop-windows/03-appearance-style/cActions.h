#pragma once

#include <QWidget>
#include <QVector>
#include <QMap>

namespace Ui
{
    class cActions;
}

class cActions : public QWidget
{
    Q_OBJECT

public:
    struct sAction
    {
        QString data;
        QString key;
        QString text;
    };

public:
    explicit cActions(QWidget *parent = 0);
    ~cActions();
    void addAction(const QString &_data, const QString &_key, const QString &_text);
    void initActions();

private:
    bool isActive(const QString &_key) const;
    bool loadAction(const QString &_key, sAction &_action) const;

private slots:
    void onAction();

signals:
    void emitAction(sAction);

private:
    Ui::cActions *ui;
    QVector<sAction> m_actions;
    QMap<QAction *, QString> m_keys;
};
