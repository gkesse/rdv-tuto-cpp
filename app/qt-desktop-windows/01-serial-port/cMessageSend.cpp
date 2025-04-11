#include "cMessageSend.h"
#include "ui_cMessageSend.h"

using namespace std::chrono_literals;

cMessageSend::cMessageSend(const QString &_message, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::cMessageSend),
      m_message(_message)
{
    ui->setupUi(this);
    ui->layLogo->setAlignment(Qt::AlignTop);
    ui->lblMessage->setText(m_message);
}

cMessageSend::~cMessageSend()
{
    delete ui;
}
