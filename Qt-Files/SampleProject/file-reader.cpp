#include <QtCore/QFile>
#include <QDebug>
#include "file-reader.h"

//connect(obj1,signal1,obj2,slot2)

FileReader::FileReader()
{
    /*register timer*/
    QObject::connect(&timer, &QTimer::timeout, this, &FileReader::timerHandler);
    timer.setInterval(1000);
    timer.start();
}

void FileReader::timerHandler()
{
    QFile file("/var/tmp/csocket-data.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice:: Text)){
        qDebug() << "Error opening socket file for reading!";
        return;
    }

    float temp = QString(file.readAll()).toDouble();
    qDebug() << "Temp received:" << temp;

    emit SigTempChanged(temp);

    //test->file.close();
}
