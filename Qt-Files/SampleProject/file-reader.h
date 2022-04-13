#ifndef FILEREADER_H
#define FILEREADER_H

#include <QtCore/QTimer>

class FileReader: public QObject{

    Q_OBJECT

public:
    FileReader();

signals:
    void SigTempChanged(float temp);

private slots:
    void timerHandler();

private:
    QTimer timer;

};

#endif // FILEREADER_H
