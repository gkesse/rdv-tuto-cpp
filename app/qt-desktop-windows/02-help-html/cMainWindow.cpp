#include "cMainWindow.h"
#include "ui_cMainWindow.h"
#include "cHelpWindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cMainWindow)
{
    ui->setupUi(this);
    QFile oFile(":/help/fr.html");
    if (!oFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Le fichier d'aide est introuvable."
                 << "filename=" << oFile.fileName();
        return;
    }
    QByteArray oFileData = oFile.readAll();
    m_helpWindow = new cHelpWindow(QString(oFileData), this);
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::on_actionHelpApp_triggered()
{
    m_helpWindow->exec();
}

void cMainWindow::on_actionAboutApp_triggered()
{
    QMessageBox::about(this, "A propos de l'application ",
                       "<b>ReadySCOPE - v1.0</b><br>"
                       "Oscilloscope numérique<br><br>"
                       "Produit par <a href='https://readydev.ovh/home'>ReadyDEV</a><br>"
                       "Plateforme de Développement Continu");
}

void cMainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}
