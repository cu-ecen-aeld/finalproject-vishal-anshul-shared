#include <QtWidgets>
#include "components.h"

Components::Components(){

    QVBoxLayout *vlayout = new QVBoxLayout;

    /* App name properties*/
    QLabel *app_name = new QLabel(tr("AESD GUI Application"));
    QFont s = app_name->font();
    s.setPointSize(25);
    s.setBold(true);
    app_name->setFont(s);
    app_name->setAlignment(Qt::AlignCenter);

    /*Temp sensor label*/
    QLabel *temp_label = new QLabel(tr("Temperature value:"));
    QFont t = temp_label->font();
    t.setPointSize(12);
    temp_label->setFont(t);
    temp_label->setAlignment(Qt::AlignCenter);

    /*Temp value label*/
    temp_v = new  QLabel(tr("Test"));
    temp_v->setFont(t);
    temp_v->setAlignment(Qt::AlignCenter);

    /*Add widgets*/
    vlayout->addWidget(app_name);
    vlayout->addWidget(temp_label);
    vlayout->addWidget(temp_v);

    setLayout(vlayout);
}

void Components::SloTempChanged(float temp)
{
    /*convert temperature from float to string
     * as QLabel needs a string*/
    temp_v->setText(QString::number(temp, 'f', 2));
}

