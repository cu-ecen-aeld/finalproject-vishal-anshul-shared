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
    void handle_button1();
    void handle_button2();

public:
    Window();

private:
    Components *components;

};

#endif // WINDOW_H
