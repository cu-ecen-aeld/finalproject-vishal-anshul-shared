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

    /*IR file read*/
    QFile file_ir("/var/tmp/ir-socket-data.txt");

    if(!file_ir.open(QIODevice::ReadOnly | QIODevice:: Text)){
        qDebug() << "Error opening socket file for reading!";
        return;
    }

    int ir = QString(file_ir.readAll()).toInt();
    qDebug() << "IR received:" << ir;

    emit SigIrChanged(ir);

    /*Full range file read*/
    QFile file_full("/var/tmp/full-socket-data.txt");

    if(!file_full.open(QIODevice::ReadOnly | QIODevice:: Text)){
        qDebug() << "Error opening socket file for reading!";
        return;
    }

    int full = QString(file_full.readAll()).toInt();
    qDebug() << "Full received:" << full;

    emit SigFullChanged(full);

    /*Visible range file read*/
    QFile file_vis("/var/tmp/vis-socket-data.txt");

    if(!file_vis.open(QIODevice::ReadOnly | QIODevice:: Text)){
        qDebug() << "Error opening socket file for reading!";
        return;
    }

    int vis = QString(file_vis.readAll()).toInt();
    qDebug() << "Vis received:" << vis;

    emit SigVisChanged(vis);


    //test->file.close();
}
