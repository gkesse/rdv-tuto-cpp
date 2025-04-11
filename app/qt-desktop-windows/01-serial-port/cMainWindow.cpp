#include "cMainWindow.h"
#include "ui_cMainWindow.h"
#include "cPortAction.h"
#include "cMessageSend.h"
#include "cMessageRecv.h"
#include <QMessageBox>
#include <QScrollBar>

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cMainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabWidget->setCurrentWidget(ui->tabSendMessagePort1);
    ui->messageLayoutPort1->setAlignment(Qt::AlignTop);
    ui->messageLayoutPort2->setAlignment(Qt::AlignTop);
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

bool cMainWindow::isActive(const QString &_portName) const
{
    for (QSerialPort *oSerialPort : m_connections)
    {
        if (oSerialPort->portName() == _portName)
        {
            if (oSerialPort->isOpen())
                return true;
        }
    }
    return false;
}

void cMainWindow::addConnection(const QString &_portName)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QTableWidgetItem *oTableWidgetItem = new QTableWidgetItem(_portName);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, oTableWidgetItem);

    cPortAction *oPortAction = new cPortAction(_portName);
    connect(oPortAction, &cPortAction::emitSendMessage, this, &cMainWindow::onSendMessage);

    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 1, oPortAction);
}

void cMainWindow::addPortToTab(const QString &_portName)
{
    switch (m_portToTab.size())
    {
    case 0:
        m_portToTab[_portName] = ui->tabSendMessagePort1;
        ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->tabSendMessagePort1), _portName);
        break;
    case 1:
        m_portToTab[_portName] = ui->tabSendMessagePort2;
        ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->tabSendMessagePort2), _portName);
        break;
    default:
        break;
    }
}

bool cMainWindow::loadConnection(const QString &_portName, QSerialPort **_serialPort) const
{
    for (QSerialPort *oSerialPort : m_connections)
    {
        if (oSerialPort->portName() == _portName)
        {
            if (oSerialPort->isOpen())
            {
                (*_serialPort) = oSerialPort;
                return true;
            }
        }
    }
    return false;
}

bool cMainWindow::loadPortToTab(const QString &_portName, QWidget **_tabWidget) const
{
    QMap<QString, QWidget *>::const_iterator it;
    for (it = m_portToTab.begin(); it != m_portToTab.end(); ++it)
    {
        if (it.key() == _portName)
        {
            (*_tabWidget) = it.value();
            return true;
        }
    }
    return false;
}

bool cMainWindow::loadPortToTab(QWidget *_oTabWidget, QString &_portName) const
{
    QMap<QString, QWidget *>::const_iterator it;
    for (it = m_portToTab.begin(); it != m_portToTab.end(); ++it)
    {
        if (it.value() == _oTabWidget)
        {
            _portName = it.key();
            return true;
        }
    }
    return false;
}

bool cMainWindow::loadPortToTab(const QString &_portName, QLayout **_layout) const
{
    QWidget *oTabWidget;
    if (!loadPortToTab(_portName, &oTabWidget))
        return false;

    if (oTabWidget == ui->tabSendMessagePort1)
    {
        (*_layout) = ui->messageLayoutPort1;
        return true;
    }
    if (oTabWidget == ui->tabSendMessagePort2)
    {
        (*_layout) = ui->messageLayoutPort2;
        return true;
    }

    return false;
}

void cMainWindow::showSendMessageTab(const QString &_portName) const
{
    QWidget *oTabWidget;
    if (!loadPortToTab(_portName, &oTabWidget))
        return;
    ui->tabWidget->setTabVisible(ui->tabWidget->indexOf(ui->tabSendMessagePort1), (oTabWidget == ui->tabSendMessagePort1));
    ui->tabWidget->setTabVisible(ui->tabWidget->indexOf(ui->tabSendMessagePort2), (oTabWidget == ui->tabSendMessagePort2));
}

void cMainWindow::clearOpenConnection()
{
    ui->edtPortName->clear();
}

void cMainWindow::clearSendMessagePort1()
{
    ui->edtSendMessagePort1->clear();
}

void cMainWindow::clearSendMessagePort2()
{
    ui->edtSendMessagePort2->clear();
}

void cMainWindow::on_actionOpenConnection_triggered()
{
    if (m_connections.size() == 2)
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le nombre maximal de connexions est atteint."));
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->pageOpenConnection);
}

void cMainWindow::on_actionDisplayConnection_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDisplayConnection);
}

void cMainWindow::on_btnOpenConnection_clicked()
{
    QString oPortName = ui->edtPortName->text();

    if (oPortName.isEmpty())
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le nom du port est obligatoire."));
        return;
    }

    if (isActive(oPortName))
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le port série est déjà ouvert."));
        return;
    }

    QSerialPort *oSerialPort = new QSerialPort(this);
    connect(oSerialPort, &QSerialPort::readyRead, this, &cMainWindow::onReadyData);
    connect(oSerialPort, &QSerialPort::errorOccurred, this, &cMainWindow::onErrorOccurred);

    oSerialPort->setPortName(oPortName);
    oSerialPort->setBaudRate(QSerialPort::Baud9600);
    oSerialPort->setDataBits(QSerialPort::Data8);
    oSerialPort->setFlowControl(QSerialPort::NoFlowControl);
    oSerialPort->setParity(QSerialPort::NoParity);
    oSerialPort->setStopBits(QSerialPort::OneStop);
    oSerialPort->open(QIODevice::ReadWrite);

    if (!oSerialPort->isOpen())
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("La connexion au port série a échoué."));

        return;
    }

    QMessageBox::information(this, tr("Messages d'informations"),
                             tr("La connexion au port série a réussi."));

    m_connections.push_back(oSerialPort);
    addConnection(oPortName);
    addPortToTab(oPortName);
    clearOpenConnection();
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
}

void cMainWindow::on_btnSendMessagePort1_clicked()
{
    QString oMessage = ui->edtSendMessagePort1->toPlainText();

    if (oMessage.isEmpty())
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le message est obligatoire."));

        return;
    }

    QString oPortName;

    if (!loadPortToTab(ui->tabSendMessagePort1, oPortName))
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le nom du port est inconnu."));

        return;
    }

    QSerialPort *oSerialPort;
    if (!loadConnection(oPortName, &oSerialPort))
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("La connexion port série est introuvable."));
        return;
    }

    cMessageSend *oMessageSend = new cMessageSend(oMessage);
    ui->messageLayoutPort1->addWidget(oMessageSend);
    ui->scrollAreaPort1->widget()->adjustSize();
    qApp->processEvents();
    ui->scrollAreaPort1->verticalScrollBar()->setValue(ui->scrollAreaPort1->verticalScrollBar()->maximum());

    oSerialPort->write(oMessage.toUtf8());

    clearSendMessagePort1();

    qDebug() << "L'envoi de message est termine."
             << "|portName=" << oSerialPort->portName()
             << "|message=" << oMessage.left(50);
}

void cMainWindow::on_btnSendMessagePort2_clicked()
{
    QString oMessage = ui->edtSendMessagePort2->toPlainText();

    if (oMessage.isEmpty())
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le message est obligatoire."));
        return;
    }

    QString oPortName;

    if (!loadPortToTab(ui->tabSendMessagePort2, oPortName))
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("Le nom du port est inconnu."));

        return;
    }

    QSerialPort *oSerialPort;
    if (!loadConnection(oPortName, &oSerialPort))
    {
        QMessageBox::critical(this, tr("Messages d'erreurs"),
                              tr("La connexion port série est introuvable."));
        return;
    }

    cMessageSend *oMessageSend = new cMessageSend(oMessage);
    ui->messageLayoutPort2->addWidget(oMessageSend);
    ui->scrollAreaPort2->widget()->adjustSize();
    qApp->processEvents();
    ui->scrollAreaPort2->verticalScrollBar()->setValue(ui->scrollAreaPort2->verticalScrollBar()->maximum());

    oSerialPort->write(oMessage.toUtf8());

    clearSendMessagePort2();

    qDebug()
        << "L'envoi de message est termine."
        << "|portName=" << oSerialPort->portName()
        << "|message=" << oMessage.left(50);
}

void cMainWindow::onReadyData()
{
    QSerialPort *oSerialPort = qobject_cast<QSerialPort *>(sender());
    QByteArray oMessage = oSerialPort->readAll();
    QString oPortName = oSerialPort->portName();
    QLayout *oMessageLayout;

    if (!loadPortToTab(oSerialPort->portName(), &oMessageLayout))
        return;

    cMessageRecv *oMessageRecv = new cMessageRecv(oMessage);
    oMessageLayout->addWidget(oMessageRecv);

    qDebug() << "La reception de message est termine."
             << "|portName=" << oSerialPort->portName()
             << "|message=" << oMessage.left(50);
}

void cMainWindow::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError)
    {
        QSerialPort *oSerialPort = qobject_cast<QSerialPort *>(sender());
        qDebug() << "La connexion au port serie a echoue."
                 << "|errorCode=" << error
                 << "|portName=" << oSerialPort->portName();
    }
}

void cMainWindow::onSendMessage(QAction *_action)
{
    QString oPortName = _action->data().toString();
    QSerialPort *oSerialPort;
    if (loadConnection(oPortName, &oSerialPort))
    {
        ui->stackedWidget->setCurrentWidget(ui->pageSendMessage);
        showSendMessageTab(oPortName);
        qDebug() << "L'envoi de message a demarre."
                 << "|portName=" << oSerialPort->portName();
    }
}
