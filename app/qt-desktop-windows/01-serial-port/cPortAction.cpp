#include "cPortAction.h"
#include "ui_cPortAction.h"
#include <QMenu>

cPortAction::cPortAction(const QString &_portName, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::cPortAction),
      m_portName(_portName)
{
    ui->setupUi(this);
    ui->layActions->setAlignment(Qt::AlignCenter);
    initActions();
}

cPortAction::~cPortAction()
{
    delete ui;
}

void cPortAction::initActions()
{
    QMenu *oMenu = new QMenu(this);

    QAction *oActions = new QAction("Envoyer un message");
    oActions->setData(m_portName);
    oMenu->addAction(oActions);
    connect(oActions, &QAction::triggered, this, &cPortAction::onSendMessage);

    ui->btnActions->setMenu(oMenu);
}

void cPortAction::onSendMessage()
{
    QAction *oActions = qobject_cast<QAction *>(sender());
    emit emitSendMessage(oActions);
}