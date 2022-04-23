#include <QApplication>
#include <QLabel>
#include <QWidget>
#include "window.h"
#include "file-reader.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    Window window;
    FileReader fr;

    /*Register temp & humidity change signal and slot*/
    QObject::connect(&fr, &FileReader::SigTempChanged, &window, &Window::SloTempChanged);
    QObject::connect(&fr, &FileReader::SigHumChanged, &window, &Window::SloHumChanged);
    QObject::connect(&fr, &FileReader::SigIrChanged, &window, &Window::SloIrChanged);
    QObject::connect(&fr, &FileReader::SigFullChanged, &window, &Window::SloFullChanged);
    QObject::connect(&fr, &FileReader::SigVisChanged, &window, &Window::SloVisChanged);

    /* Main window properties*/
    window.setFixedSize(1280,720);
    window.setStyleSheet("background-color: lightblue;");
    window.show();

    return app.exec();
}
