#include <QtWidgets>
#include "layout.h"

Layouts::Layouts(){
    QVBoxLayout *layout = new QVBoxLayout;

    /* App name properties*/
    QLabel *app_name = new QLabel(tr("AESD GUI Application"));
    QFont s = app_name->font();
    s.setPointSize(50);
    s.setBold(true);
    app_name->setFont(s);
    app_name->setAlignment(Qt::AlignLeft);



    /*Add and set widget*/
    layout->addWidget(app_name);

    setLayout(layout);
}
