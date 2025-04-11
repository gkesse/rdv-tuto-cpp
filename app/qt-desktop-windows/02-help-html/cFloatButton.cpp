#include "cFloatButton.h"
#include "ui_cFloatButton.h"
#include <QMouseEvent>

using namespace std::chrono_literals;

cFloatButton::cFloatButton(const QString &_iconLabel, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::cFloatButton),
      m_iconLabel(_iconLabel)
{
    ui->setupUi(this);
    adjustSize();

    QFont font;
    font.setFamily("FontAwesome");
    font.setPixelSize(20);

    ui->lblButton->setFont(font);
    ui->lblButton->setText(m_iconLabel);
    ui->lblButton->installEventFilter(this);
}

cFloatButton::~cFloatButton()
{
    delete ui;
}

bool cFloatButton::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->lblButton && event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *oMouseEvent = static_cast<QMouseEvent *>(event);
        if (oMouseEvent->button() == Qt::LeftButton)
        {
            emit emitClicked();
            return true;
        }
    }
    return false;
}
