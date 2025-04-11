#include "cMainWindow.h"
#include "ui_cMainWindow.h"
#include <QStyleFactory>
#include <QMessageBox>
#include <QLabel>

const QString ACTION_APPLY_STYLE = "ACTION_APPLY_STYLE";

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cMainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList oThemes = QStyleFactory::keys();
    for (const auto &oTheme : oThemes)
    {
        qDebug() << "La detection du style d'apparence a reussi."
                 << "|theme=" << oTheme;

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *oTableWidgetItem = new QTableWidgetItem(oTheme);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, oTableWidgetItem);

        cActions *oActions = new cActions;
        oActions->addAction(oTheme, ACTION_APPLY_STYLE, "Appliquer le style");
        oActions->initActions();
        connect(oActions, &cActions::emitAction, this, &cMainWindow::onAction);

        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 1, oActions);
    }

    qDebug() << "La detection du style en cours est termine."
             << "|style=" << qApp->style()->name();

    m_themeStatus = new QLabel;
    statusBar()->addWidget(m_themeStatus);
    m_themeStatus->setText(tr("Thème : %1").arg(qApp->style()->name()));
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::on_actionHomePage_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
}

void cMainWindow::on_actionThemePage_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageTheme);
}

void cMainWindow::onAction(const sAction &_action)
{
    qDebug() << "L'action est en cours d'application."
             << "|data=" << _action.data
             << "|key=" << _action.key
             << "|text=" << _action.text;
    if (_action.key == ACTION_APPLY_STYLE)
    {
        qApp->setStyle(_action.data);
        m_themeStatus->setText(tr("Thème : %1").arg(qApp->style()->name()));
    }
}
