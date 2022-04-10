#include <QApplication>
#include <QLabel>
#include <QWidget>
#include "window.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    Window window;

    /* Main window properties*/
    window.setFixedSize(720,480);
    window.setStyleSheet("background-color: cyan;");
    window.show();

    return app.exec();
}
