#include "modeling.h"
#include "ui_modeling.h"

modeling::modeling(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modeling)
{
    std::srand(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);
    ui->setupUi(this);


}

modeling::~modeling()
{
    delete ui;
}


