#include <QtWidgets>
#include <QMessageBox>
#include "components.h"
#include "window.h"

/*
* A signal is a message that an object can send, most of the time to inform of a status change.
* A slot is a function that is used to accept and respond to a signal. From - https://wiki.qt.io/Qt_for_Beginners.
* Read uptil - Transmitting information.
*/
//connect(obj1,signal1,obj2,slot2)

Window::Window()
{
    components = new Components;
    QVBoxLayout *vlayout = new QVBoxLayout;//main vertical layout
    QHBoxLayout *hlayout = new QHBoxLayout;

    /*Buttons*/
    QPushButton *button1 = new QPushButton("Button-1");
    QPushButton *button2 = new QPushButton("Button-2");
    button1->setStyleSheet("background-color:red;font-size: 25px;height: 36px;width: 80px;");
    button2->setStyleSheet("background-color:orange;font-size: 25px;height: 36px;width: 80px;");

    /*Button action*/
    connect(button1,SIGNAL(clicked()),this,SLOT(handle_button1()));
    connect(button2,SIGNAL(clicked()),this,SLOT(handle_button2()));

    hlayout->addWidget(button1);
    hlayout->addWidget(button2);

    vlayout->addWidget(components);//vertical-layout within vertical-layout
    vlayout->addLayout(hlayout);//horizontal-layout within vertical-layout


    setLayout(vlayout);

}

void Window::handle_button1(){

    QMessageBox *msgbox = new QMessageBox;

    QFile *file = new QFile ("/var/tmp/tmplog.txt");

    if (file->open (QIODevice::ReadOnly) == true)
    {
        msgbox->setText(QString (file->readAll ()));
        file->close();
    }

    msgbox->exec();

}

void Window::handle_button2(){

}
