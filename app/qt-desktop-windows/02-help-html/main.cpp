#include "cMainWindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString oFontFile(":/font/fontawesome-webfont.ttf");
    int id = QFontDatabase::addApplicationFont(oFontFile);
    if (id == -1)
    {
        qDebug() << "Le chargement de la police a echoue."
                 << "|fontFile=" << oFontFile;
    }
    else
    {
        QStringList oFontFamilies = QFontDatabase::applicationFontFamilies(id);
        qDebug() << "Le chargement de la police a reussi."
                 << "|fontFile=" << oFontFile
                 << "|fontFamilies=" << oFontFamilies;
    }

    cMainWindow *oMainWindow = new cMainWindow;
    oMainWindow->resize(400, 200);
    oMainWindow->show();
    return app.exec();
}
