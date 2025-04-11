#include "cActions.h"
#include "ui_cActions.h"
#include <QMenu>

cActions::cActions(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::cActions)
{
    ui->setupUi(this);
    ui->layActions->setAlignment(Qt::AlignCenter);
}

cActions::~cActions()
{
    delete ui;
}

void cActions::addAction(const QString &_data, const QString &_key, const QString &_text)
{
    if (!isActive(_key))
    {
        sAction oAction{_data, _key, _text};
        m_actions.push_back(oAction);
    }
    else
    {
        qDebug() << "L'action a ete deja ajoutee a la liste."
                 << "|data=" << _data
                 << "|key=" << _key
                 << "|text=" << _text;
    }
}

void cActions::initActions()
{
    if (m_actions.isEmpty())
    {
        qDebug() << "Aucune action n'a ete ajoutee à liste";
        return;
    }

    QMenu *oMenu = new QMenu(this);

    for (const auto &oAction : m_actions)
    {
        QAction *iAction = new QAction(oAction.text);
        iAction->setData(oAction.data);
        connect(iAction, &QAction::triggered, this, &cActions::onAction);
        m_keys[iAction] = oAction.key;
        oMenu->addAction(iAction);
    }

    ui->btnActions->setMenu(oMenu);
}

bool cActions::isActive(const QString &_key) const
{
    for (const auto &oAction : m_actions)
    {
        if (oAction.key == _key)
        {
            return true;
        }
    }
    return false;
}

bool cActions::loadAction(const QString &_key, sAction &_action) const
{
    for (const auto &oAction : m_actions)
    {
        if (oAction.key == _key)
        {
            _action = oAction;
            return true;
        }
    }
    return false;
}

void cActions::onAction()
{
    QAction *oAction = qobject_cast<QAction *>(sender());
    QString oKey = m_keys[oAction];
    sAction iAction;
    if (loadAction(oKey, iAction))
    {
        emit emitAction(iAction);
    }
}