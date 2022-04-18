#include <QtWidgets>
#include <QProgressBar>
#include "components.h"

//connect(obj1,signal1,obj2,slot2)

Components::Components(){

    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout_t = new QVBoxLayout;
    QVBoxLayout *vlayout_h = new QVBoxLayout;

    /* App name properties*/
    QLabel *app_name = new QLabel(tr("AESD GUI Application"));
    QFont s = app_name->font();
    s.setPointSize(75);
    s.setBold(true);
    app_name->setFont(s);
    app_name->setAlignment(Qt::AlignCenter);

    /*Temp sensor label*/
    QLabel *temp_label = new QLabel(tr("Temperature:"));
    QFont t = temp_label->font();
    t.setPointSize(50);
    temp_label->setFont(t);
    temp_label->setAlignment(Qt::AlignLeft);

    /*Temp value label*/
    temp_v = new  QLabel(tr("Test"));
    temp_v->setFont(t);
    temp_v->setAlignment(Qt::AlignLeft);

    /*Progress Bar*/
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);

    /*Temperature vlayout_1*/
    vlayout_t->addWidget(temp_label);
    vlayout_t->addWidget(temp_v);
    vlayout_t->addWidget(progressBar);

    /*Humi sensor label*/
    QLabel *humi_label = new QLabel(tr("Humidity:"));
    QFont h = humi_label->font();
    h.setPointSize(50);
    humi_label->setFont(h);
    humi_label->setAlignment(Qt::AlignCenter);

    /*Humi value label*/
    humi_v = new  QLabel(tr("Humi"));
    humi_v->setFont(h);
    humi_v->setAlignment(Qt::AlignCenter);

    /*Humidity vlayout_2*/
    vlayout_h->addWidget(humi_label);
    vlayout_h->addWidget(humi_v);

    /*Temp and humidity side-by-side*/
    hlayout->addLayout(vlayout_t);
    hlayout->addLayout(vlayout_h);

    /*Add final widgets*/
    vlayout->addWidget(app_name);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);
}

void Components::SloTempChanged(float temp)
{
    /*convert temperature from float to string
     * as QLabel needs a string*/
    temp_v->setText(QString::number(temp, 'f', 2));
    progressBar->setValue((int)temp);
}

void Components::SloHumChanged(float hum)
{
    /*convert humidity from float to string
     * as QLabel needs a string*/
    humi_v->setText(QString::number(hum, 'f', 2));

}
