#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class Layouts;
class QPushButton;

/*
* Window class definition for handling main GUI window
*
*/

class AesdWindow : public QWidget
{
    Q_OBJECT

public slots:

public:
    AesdWindow();

private:
    Layouts *layouts;
    QPushButton *m_button;
};

#endif // WINDOW_H
