#include <QtWidgets>
#include <QProgressBar>
#include "components.h"

//connect(obj1,signal1,obj2,slot2)

Components::Components(){

    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout_t = new QVBoxLayout;
    QVBoxLayout *vlayout_h = new QVBoxLayout;
    QVBoxLayout *vlayout_i = new QVBoxLayout;
    QVBoxLayout *vlayout_f = new QVBoxLayout;
    QVBoxLayout *vlayout_v = new QVBoxLayout;
    QHBoxLayout *hlayout_i_f = new QHBoxLayout;

    /* App name properties*/
    QLabel *app_name = new QLabel(tr("Multipurpose remote monitoring"));
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
    //vlayout_t->addWidget(progressBar);

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

    /*IR Sensor label*/
    QLabel *ir_label = new QLabel(tr("IR value:"));
    QFont i = humi_label->font();
    i.setPointSize(25);
    ir_label->setFont(i);
    ir_label->setAlignment(Qt::AlignCenter);

    /*IR value label*/
    ir_v = new  QLabel(tr("ir"));
    ir_v->setFont(i);
    ir_v->setAlignment(Qt::AlignCenter);

    /*Ir vlayout_3*/
    vlayout_i->addWidget(ir_label);
    vlayout_i->addWidget(ir_v);

    /*FULL Sensor label*/
    QLabel *full_label = new QLabel(tr("Full range value:"));
    QFont f = full_label->font();
    f.setPointSize(25);
    full_label->setFont(f);
    full_label->setAlignment(Qt::AlignCenter);

    /*Full value label*/
    full_v = new  QLabel(tr("full"));
    full_v->setFont(f);
    full_v->setAlignment(Qt::AlignCenter);

    /*Full vlayout_4*/
    vlayout_f->addWidget(full_label);
    vlayout_f->addWidget(full_v);

    /*IR and full side-by-side*/
    hlayout_i_f->addLayout(vlayout_i);
    hlayout_i_f->addLayout(vlayout_f);

    /*Visible Sensor label*/
    QLabel *vis_label = new QLabel(tr("Visible range value:"));
    QFont v = vis_label->font();
    v.setPointSize(25);
    vis_label->setFont(v);
    vis_label->setAlignment(Qt::AlignCenter);

    /*Visible value label*/
    vis_v = new  QLabel(tr("visible"));
    vis_v->setFont(v);
    vis_v->setAlignment(Qt::AlignCenter);

    /*Visible vlayout_5*/
    vlayout_v->addWidget(vis_label);
    vlayout_v->addWidget(vis_v);

    /*Add final widgets*/
    vlayout->addWidget(app_name);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(hlayout_i_f);
    vlayout->addLayout(vlayout_v);

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


void Components::SloIrChanged(int ir)
{
    /*convert ir from int to string
     * as QLabel needs a string*/
    ir_v->setText(QString::number(ir));

}

void Components::SloFullChanged(int full)
{
    /*convert full from int to string
     * as QLabel needs a string*/
    full_v->setText(QString::number(full));

}

void Components::SloVisChanged(int vis)
{
    /*convert vis from int to string
     * as QLabel needs a string*/
    vis_v->setText(QString::number(vis));

}
