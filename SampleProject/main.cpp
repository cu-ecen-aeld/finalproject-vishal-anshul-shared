#include <QApplication>
#include <QLabel>
#include <QWidget>
#include "mainwindow.h"
#include "aesdwindow.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    AesdWindow aesdwindow;

    /* Main window properties*/
    aesdwindow.setFixedSize(720,480);
    aesdwindow.setStyleSheet("background-color: yellow;");
    aesdwindow.show();

    return app.exec();
}
