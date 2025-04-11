#include "cMainWindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    cMainWindow *oMainWindow = new cMainWindow;
    oMainWindow->resize(640, 480);
    oMainWindow->show();
    return app.exec();
}
