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

    /*Test buttons*/
    QPushButton *button1 = new QPushButton("Button-1");
    QPushButton *button2 = new QPushButton("Button-2");
    button1->setStyleSheet("background-color:yellow");
    button2->setStyleSheet("background-color:pink");

    /*Add and set widget*/
    vlayout->addWidget(button1);
    vlayout->addWidget(button2);
    vlayout->addWidget(app_name);

    setLayout(vlayout);
}
