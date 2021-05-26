#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tab_2, SIGNAL(start_modelling(int)),
            ui->tabWidget, SLOT(setCurrentIndex(int)));
    connect(ui->tab_2, SIGNAL(set_json(QString)),
            ui->tab, SLOT(accept_json(QString)));

//    ui->tabWidget->setCurrentIndex(0);
    need_progess_bar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::need_progess_bar()
{
//    v_futureWatcher.append(new QFutureWatcher<void>());
//    v_progress.append(new QProgressDialog());
//    v_futureInterface.append(new QFutureInterface<void>());

//    int id = v_progress.size() - 1;

//    v_progress[id]->setWindowTitle("Read bin data");
//    v_progress[id]->setLabelText("Reading reg");
//    v_progress[id]->setRange(0,100);
//    v_progress[id]->setObjectName("sessions[current_session]->");
//    v_progress[id]->setWindowFlags(Qt::WindowStaysOnTopHint);

////    //Обновление формы после чтения файла регистрации
////    connect(v_futureWatcher[id], SIGNAL(finished()),
////            this,SLOT(slot_update_ui()));
//    //Изменение значений прогрессбара
//    connect(v_futureWatcher[id], SIGNAL(progressValueChanged(int)),
//            v_progress[id],SLOT(setValue(int)));
//    //Остановка потока при закрытии прогресс бара
//    connect(v_progress[id], SIGNAL(canceled()),
//            v_futureWatcher[id],SLOT(cancel()));


//    QtConcurrent::run(&widget_modelset::start_modelling()                      *v_futureInterface[id]);

//    v_futureWatcher[id]->setFuture(v_futureInterface[id]->future());
//    v_progress[id]->show();
}
