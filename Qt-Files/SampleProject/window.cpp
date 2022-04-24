#include <QtWidgets>
#include <QMessageBox>
#include <stdio.h>
#include <gpiod.h>
#include <unistd.h>
#include <QDebug>
#include "components.h"
#include "window.h"

#define LED_PIN         4
#define RPI_COMPILE     1
int led_status = 0;

#if (RPI_COMPILE == 1)
    struct gpiod_chip *chip;
    struct gpiod_line *line;
#endif
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
    QHBoxLayout *hlayout_2 = new QHBoxLayout;

    /*Buttons*/
    QPushButton *button1 = new QPushButton("Turn light on");
    QPushButton *offButton = new QPushButton("Turn light off");
    QPushButton *statusButton = new QPushButton("Get light status");
    QPushButton *button2 = new QPushButton("View Logs");
    button1->setStyleSheet("background-color:lightgreen;font-size: 25px;height: 36px;width: 80px;");
    button2->setStyleSheet("background-color:orange;font-size: 25px;height: 36px;width: 80px;");
    offButton->setStyleSheet("background-color:red;font-size: 25px;height: 36px;width: 80px;");
    statusButton->setStyleSheet("background-color:yellow;font-size: 25px;height: 36px;width: 80px;");

    /*Button action*/
    connect(button1,SIGNAL(clicked()),this,SLOT(handle_button1()));
    connect(button2,SIGNAL(clicked()),this,SLOT(handle_button2()));
    connect(statusButton,SIGNAL(clicked()),this,SLOT(handle_statusButton()));
    connect(offButton,SIGNAL(clicked()),this,SLOT(handle_offButton()));

    hlayout->addWidget(button1);
    hlayout->addWidget(button2);

    hlayout_2->addWidget(offButton);
    hlayout_2->addWidget(statusButton);

    vlayout->addWidget(components);//vertical-layout within vertical-layout
    vlayout->addLayout(hlayout);//horizontal-layout within vertical-layout
    vlayout->addLayout(hlayout_2);


    setLayout(vlayout);

}

int Window::handle_button1(){

    printf("TOGGLE GPIO\n");
#if (RPI_COMPILE == 1)
    int retv;

    if(led_status == 0){
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip){
        qDebug() << "Error opening GPIO chip!";
       return -1;
    }

    //Get the handle to GPIO line at given offset
    line = gpiod_chip_get_line(chip, LED_PIN);
    if(line == 0){
        gpiod_chip_close(chip);
        qDebug() << "Error getting GPIO line!";
        return -1;
    }

    //set GPIO direction output
    retv = gpiod_line_request_output(line, "foobar", 1);
    if (retv)
    {
     gpiod_chip_close(chip);
     qDebug() << "Error setting GPIO output!";
     return -1;
    }

        led_status = 1;
        retv = gpiod_line_set_value(line, led_status);
        qDebug() << "Setting led value to:" << led_status;
        printf("Setting led value to:%d\n",led_status);
        if(retv == -1){
            qDebug() << "Error writing value to GPIO!";
        }
    }

    /*
    sleep(3);

    gpiod_chip_close(chip);
    */

#endif
    return 0;
}

int Window::handle_offButton(){

#if (RPI_COMPILE == 1)
    int retv;

    if(led_status ==1){
        led_status = 0;
        retv = gpiod_line_set_value(line, led_status);
        qDebug() << "Setting led value to:" << led_status;
        if(retv == -1){
            qDebug() << "Error writing value to GPIO!";
        }

        sleep(1);

        gpiod_chip_close(chip);
    }

#endif
    return 0;
}

int Window::handle_statusButton(){

    QMessageBox *msgBox = new QMessageBox;

    msgBox->setWindowTitle("GPIO status");

    if(led_status == 1)
        msgBox->setText("GPIO status:1");
    else
        msgBox->setText("GPIO status:0");

    msgBox->exec();

    return 0;
}

void Window::SloTempChanged(float temp)
{
    components->SloTempChanged(temp);
}

void Window::SloHumChanged(float hum){

    components->SloHumChanged(hum);

}

void Window::SloIrChanged(int ir)
{
    components->SloIrChanged(ir);
}

void Window::SloFullChanged(int full){

    components->SloFullChanged(full);

}

void Window::SloVisChanged(int vis){

    components->SloVisChanged(vis);

}

void Window::handle_button2()
{
    //Add log file open.
    QMessageBox *msgBox = new QMessageBox;

    msgBox->setWindowTitle("Sensors logs");

    QFile logFile("/var/tmp/log-file.txt");

    if(logFile.open(QIODevice::ReadOnly) == true){
        msgBox->setText(QString(logFile.readAll()));
        logFile.close();
    }

    msgBox->exec();

}
