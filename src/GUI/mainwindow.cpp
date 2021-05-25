#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tab_2, SIGNAL(set_json(QString)),
              ui->tab, SLOT(set_name_json(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


