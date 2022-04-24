#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class Components;

/*
* Window class definition for handling main GUI window
*
*/

class Window : public QWidget
{
    Q_OBJECT

public slots:
    int handle_button1();
    void handle_button2();
    int handle_statusButton();
    int handle_offButton();
    void SloTempChanged(float temp);
    void SloHumChanged(float hum);
    void SloIrChanged(int ir);
    void SloFullChanged(int full);
    void SloVisChanged(int vis);

public:
    Window();

private:
    Components *components;

};

#endif // WINDOW_H
