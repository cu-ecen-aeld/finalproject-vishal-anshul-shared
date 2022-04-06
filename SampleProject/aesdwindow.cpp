#include <QtWidgets>
#include "layout.h"
#include "aesdwindow.h"
/*
* A signal is a message that an object can send, most of the time to inform of a status change.
* A slot is a function that is used to accept and respond to a signal. From - https://wiki.qt.io/Qt_for_Beginners.
* Read uptil - Transmitting information.
*/

AesdWindow::AesdWindow()
{
    layouts = new Layouts;
    QVBoxLayout *layout = new QVBoxLayout;

    /*Create and position the button */
    m_button = new QPushButton("Button-1",this);
    m_button->setGeometry(300,300,80,30);

    //layout->addWidget(layouts);
    //setLayout(layout);

}
