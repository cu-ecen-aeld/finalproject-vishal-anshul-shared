#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "layout.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    layouts = new Layouts;
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(layouts);

    setLayout(layout);

    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

