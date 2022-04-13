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


class Components : public QWidget
{
    Q_OBJECT

public:
    Components();

public slots:
    void SloTempChanged(float temp);

private:
    QLabel *temp_v;

};

#endif // LAYOUT_H
