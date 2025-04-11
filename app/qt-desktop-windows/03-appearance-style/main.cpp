#include "cMainWindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    cMainWindow *oMainWindow = new cMainWindow;
    oMainWindow->resize(400, 200);
    oMainWindow->show();
    return app.exec();
}
