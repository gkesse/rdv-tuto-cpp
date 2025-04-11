#include "cHelpWindow.h"
#include "ui_cHelpWindow.h"
#include "cFloatButton.h"
#include <QLabel>
#include <QResizeEvent>
#include <QScrollBar>

using namespace std::chrono_literals;

cHelpWindow::cHelpWindow(const QString &_message, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::cHelpWindow),
      m_message(_message)
{
    ui->setupUi(this);
    ui->txtHelp->setHtml(m_message);
    resize(600, 300);
    m_bottomLink = new cFloatButton(ICON_FA_CHEVRON_DOWN, this);
    connect(m_bottomLink, &cFloatButton::emitClicked, this, &cHelpWindow::onOpenBottomLink);
    m_topLink = new cFloatButton(ICON_FA_CHEVRON_UP, this);
    connect(m_topLink, &cFloatButton::emitClicked, this, &cHelpWindow::onOpenTopLink);
}

cHelpWindow::~cHelpWindow()
{
    delete ui;
}

void cHelpWindow::resizeEvent(QResizeEvent *event)
{
    m_bottomLink->move(width() - 75 - 50, height() - 85);
    m_topLink->move(width() - 75, height() - 85);
}

void cHelpWindow::onOpenTopLink()
{
    QScrollBar *oScrollBar = ui->txtHelp->verticalScrollBar();
    oScrollBar->setValue(0);
}

void cHelpWindow::onOpenBottomLink()
{
    QScrollBar *oScrollBar = ui->txtHelp->verticalScrollBar();
    oScrollBar->setValue(oScrollBar->maximum());
}
