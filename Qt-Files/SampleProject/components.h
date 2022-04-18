#ifndef LAYOUT_H
#define LAYOUT_H

#include <QWidget>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

class QLabel;
class QProgressBar;

class Components : public QWidget
{
    Q_OBJECT

public:
    Components();

public slots:
    void SloTempChanged(float temp);
    void SloHumChanged(float hum);

private:
    QLabel *temp_v;
    QLabel *humi_v;
    QProgressBar *progressBar;

};

#endif // LAYOUT_H
