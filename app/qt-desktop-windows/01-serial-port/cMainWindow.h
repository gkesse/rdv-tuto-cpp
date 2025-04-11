#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QVector>
#include <QMap>

namespace Ui
{
    class cMainWindow;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit cMainWindow(QWidget *parent = 0);
    ~cMainWindow();

private:
    bool isActive(const QString &_portName) const;
    void addConnection(const QString &_portName);
    void addPortToTab(const QString &_portName);
    bool loadConnection(const QString &_portName, QSerialPort **_serialPort) const;
    bool loadPortToTab(const QString &_portName, QWidget **_tabWidget) const;
    bool loadPortToTab(QWidget *_oTabWidget, QString &_portName) const;
    bool loadPortToTab(const QString &_portName, QLayout **_layout) const;
    void showSendMessageTab(const QString &_portName) const;
    void clearOpenConnection();
    void clearSendMessagePort1();
    void clearSendMessagePort2();

private slots:
    void on_actionOpenConnection_triggered();
    void on_actionDisplayConnection_triggered();
    void on_btnOpenConnection_clicked();
    void on_btnSendMessagePort1_clicked();
    void on_btnSendMessagePort2_clicked();
    void onReadyData();
    void onErrorOccurred(QSerialPort::SerialPortError error);
    void onSendMessage(QAction *_action);

private:
    Ui::cMainWindow *ui;
    QVector<QSerialPort *> m_connections;
    QMap<QString, QWidget *> m_portToTab;
};
