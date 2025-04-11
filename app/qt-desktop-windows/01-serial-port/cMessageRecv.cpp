#include "cMessageRecv.h"
#include "ui_cMessageRecv.h"

using namespace std::chrono_literals;

cMessageRecv::cMessageRecv(const QString &_message, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::cMessageRecv),
      m_message(_message)
{
    ui->setupUi(this);
    ui->layLogo->setAlignment(Qt::AlignTop);
    ui->lblMessage->setText(m_message);
}

cMessageRecv::~cMessageRecv()
{
    delete ui;
}
