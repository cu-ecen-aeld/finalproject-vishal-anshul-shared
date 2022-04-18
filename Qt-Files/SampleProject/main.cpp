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

    /* Main window properties*/
    window.setFixedSize(720,480);
    window.setStyleSheet("background-color: cyan;");
    window.show();

    return app.exec();
}
