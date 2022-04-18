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
    /*Temp file read*/
    QFile file_tmp("/var/tmp/tmp-socket-data.txt");

    if(!file_tmp.open(QIODevice::ReadOnly | QIODevice:: Text)){
        qDebug() << "Error opening socket file for reading!";
        return;
    }

    float temp = QString(file_tmp.readAll()).toDouble();
    qDebug() << "Temp received:" << temp;

    emit SigTempChanged(temp);

    /*Hum file read*/
    QFile file_hum("/var/tmp/hum-socket-data.txt");

    if(!file_hum.open(QIODevice::ReadOnly | QIODevice:: Text)){
        qDebug() << "Error opening socket file for reading!";
        return;
    }

    float hum = QString(file_hum.readAll()).toDouble();
    qDebug() << "Hum received:" << hum;

    emit SigHumChanged(hum);

    //test->file.close();
}
