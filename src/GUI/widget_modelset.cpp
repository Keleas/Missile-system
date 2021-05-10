#include "widget_modelset.h"
#include "ui_widget_modelset.h"

widget_modelset::widget_modelset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_modelset)
{
    ui->setupUi(this);


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("models_data.db");
    if (!db.open())
        QMessageBox::critical(0,"DB Error",db.lastError().text());

    ui->customPlot->setInteractions(QCP::iSelectAxes |
                                    QCP::iSelectLegend |
                                    QCP::iSelectPlottables);

//    QIcon icon(":/src/images/pu.png");

    ui->customPlot->xAxis->setRange(-1000, 1000);
    ui->customPlot->yAxis->setRange(-1000, 1000);

    ui->customPlot->xAxis->setLabel("x, km");
    ui->customPlot->yAxis->setLabel("y, km");

    create_stationary_elements();

//    ui->pushButton_pu->setIcon(icon);
//    ui->pushButton_pu->setIconSize(QSize(48,48));

    ui->pushButton_radar->setCheckable(true);
    ui->pushButton_la->setCheckable(true);
    ui->pushButton_pu->setCheckable(true);
    ui->pushButton_pbu->setCheckable(true);

    connect(ui->pushButton_radar, SIGNAL(toggled(bool)),
            this, SLOT(button_radar_toggled(bool)));
    connect(ui->pushButton_la, SIGNAL(toggled(bool)),
            this, SLOT(button_la_toggled(bool)));
    connect(ui->pushButton_pu, SIGNAL(toggled(bool)),
            this, SLOT(button_pu_toggled(bool)));
    connect(ui->pushButton_pbu, SIGNAL(toggled(bool)),
            this, SLOT(button_pbu_toggled(bool)));

    top_item_pbu = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_pbu);
    top_item_pbu->setText(0,"ПБУ");

    top_item_radar = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_radar);
    top_item_radar->setText(0,"РЛС");

    top_item_pu = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_pu);
    top_item_pu->setText(0,"ПУ");

    top_item_la = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_la);
    top_item_la->setText(0,"ЛА");

    item_pbu = new QTreeWidgetItem();
}

widget_modelset::~widget_modelset()
{
    delete ui;
}


void widget_modelset::click_on_canvas(QMouseEvent *event)
{
    QString cord;
    double x = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = ui->customPlot->yAxis->pixelToCoord(event->pos().y());
    cord = "x = "+QString::number(x)+", y = "+QString::number(y);
    ui->lineEdit->setText(cord);

    switch (state_buttons)
    {
    case state_la:
    {
        add_point(x,y);
        plot(index_la, vector_x_la, vector_y_la);
        if (item_la_added==false)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            int count = vector_item_la.size();
            top_item_la->addChild(item);
            item->setText(0, "ЛА_"+QString::number(count));
            add_basic_items_la(item, count);
            add_children_items_la(x, y,item);
            vector_item_la.append(item);
            item_la_added = true;
        }
        else
        {
            add_children_items_la(x, y, vector_item_la.last());
        }
    }break;
    case state_pbu:
    {
        add_point(x,y);
        plot(state_pbu, x_pbu, y_pbu);
        remove_tree_items(top_item_pbu);
        vector_data_pbu.clear();
        top_item_pbu->addChild(item_pbu);
        QList<QString> list;
        list<<"ID: 0"
            <<"x: "+QString::number(x)
            <<"y: "+QString::number(y)
            <<"z: 0";
        for (int ii=0;ii<list.size() ; ++ii)
        {
             QTreeWidgetItem* item = new QTreeWidgetItem();
             item_pbu->addChild(item);
             item->setText(0,list.at(ii));             
             vector_data_pbu.append(list.at(ii).split(": ").at(1));
        }
        item_pbu->setText(0,"ПБУ");
    }break;
    case state_pu:
    {
        add_point(x,y);
        plot(state_pu, vector_x_pu, vector_y_pu);
        add_children_items_pu(x,y);
    }break;
    case state_radar:
    {
        add_point(x,y);
        plot(state_radar, vector_x_radar, vector_y_radar);
        add_children_items_radar(x,y);
    }break;
    }
}

void widget_modelset::add_point(double x, double y)
{
    switch (state_buttons)
    {
    case state_la:
    {
        vector_x_la.append(x);
        vector_y_la.append(y);
    }break;
    case state_pbu:
    {
        x_pbu.clear();
        y_pbu.clear();
        x_pbu.append(x);
        y_pbu.append(y);
    }break;
    case state_pu:
    {
        vector_x_pu.append(x);
        vector_y_pu.append(y);
    }break;
    case state_radar:
    {
        vector_x_radar.append(x);
        vector_y_radar.append(y);
    }break;
    }

}

void widget_modelset::clearData()
{
    vector_x_radar.clear();
    vector_y_radar.clear();
    vector_x_la.clear();
    vector_y_la.clear();
    vector_x_pu.clear();
    vector_y_pu.clear();
    vector_item_la.clear();
    vector_item_radar.clear();
    vector_item_pu.clear();
    vector_data_la.clear();
    vector_data_pbu.clear();
    vector_data_pu.clear();
    vector_data_radar.clear();
    vector_data_la_all.clear();
    x_pbu.clear();
    y_pbu.clear();
    name_config.clear();
    remove_tree_items(top_item_pbu);
    remove_tree_items(top_item_la);
    remove_tree_items(top_item_pu);
    remove_tree_items(top_item_radar);
    index_la=0;
}

void widget_modelset::plot(int number,
                           QVector<double> vector_x,
                           QVector<double> vector_y)
{
    ui->customPlot->graph(number)->setData(vector_x,vector_y,true);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void widget_modelset::button_radar_toggled(bool state)
{
    if(state==true)//Кнопка зажата
    {
        set_state_buttons(state_radar);
        connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));        
    }
    else//Кнопка отжата
    {
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
    }
}

void widget_modelset::button_pu_toggled(bool state)
{
    if(state==true)//Кнопка зажата
    {
        set_state_buttons(state_pu);
        connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
    }
    else//Кнопка отжата
    {
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));

    }
}

void widget_modelset::button_pbu_toggled(bool state)
{
    if(state==true)//Кнопка зажата
    {
        set_state_buttons(state_pbu);
        connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
    }
    else//Кнопка отжата
    {
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
    }
}

void widget_modelset::button_la_toggled(bool state)
{
    if(state==true)//Кнопка зажата
    {
        set_state_buttons(state_la);
        ui->customPlot->addGraph();
        index_la = (ui->customPlot->graphCount())-1;
        vector_x_la.clear();
        vector_y_la.clear();
        QPen pen_line(Qt::red, 3, Qt::DashDotLine,
                 Qt::RoundCap, Qt::RoundJoin);
        QColor color( qrand() % ((255 + 1) - 0) + 0,
                      qrand() % ((255 + 1) - 0) + 0,
                      qrand() % ((255 + 1) - 0) + 0, 255 );
        pen_line.setColor(color);
        ui->customPlot->graph(index_la)->
                setScatterStyle(QCPScatterStyle::ssCircle);
        ui->customPlot->graph(index_la)->setLineStyle(QCPGraph::lsLine);
        ui->customPlot->graph(index_la)->setPen(pen_line);
//        connect(ui->customPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)),
//                this, SLOT(add_maneuver(QMouseEvent*)));
        connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
    }
    else//Кнопка отжата
    {
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
        item_la_added = false;
        vector_data_la_all.append(vector_data_la);
        vector_data_la.clear();
    }
}


void widget_modelset::set_state_buttons(int state)
{
    state_buttons = state;
    switch (state)
    {
    case state_la:
    {
       ui->pushButton_pbu->setChecked(false);
       ui->pushButton_pu->setChecked(false);
       ui->pushButton_radar->setChecked(false);
    }break;
    case state_pbu:
    {
        ui->pushButton_la->setChecked(false);
        ui->pushButton_pu->setChecked(false);
        ui->pushButton_radar->setChecked(false);
    }break;
    case state_pu:
    {
        ui->pushButton_la->setChecked(false);
        ui->pushButton_pbu->setChecked(false);
        ui->pushButton_radar->setChecked(false);
    }break;
    case state_radar:
    {
        ui->pushButton_la->setChecked(false);
        ui->pushButton_pu->setChecked(false);
        ui->pushButton_pbu->setChecked(false);
    }break;
    default:
    {
        ui->pushButton_la->setChecked(false);
        ui->pushButton_pbu->setChecked(false);
        ui->pushButton_pu->setChecked(false);
        ui->pushButton_radar->setChecked(false);
    }break;
    }
}

void widget_modelset::on_pushButton_clear_clicked()
{
    clearData();
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    ui->customPlot->update();
    create_stationary_elements();
    set_state_buttons(777);
}

void widget_modelset::create_stationary_elements()
{
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    QPen pen(Qt::green, 6, Qt::DashDotDotLine,
             Qt::RoundCap, Qt::RoundJoin);
    //radar
    ui->customPlot->graph(state_radar)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(state_radar)->
            setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot->graph(state_radar)->setPen(pen);
    //pu
    pen.setColor(Qt::blue);
    ui->customPlot->graph(state_pu)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(state_pu)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(state_pu)->setPen(pen);
    //pbu
    pen.setColor(Qt::darkMagenta);
    ui->customPlot->graph(state_pbu)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(state_pbu)->
            setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot->graph(state_pbu)->setPen(pen);
}

//int widget_modelset::get_state_buttons()
//{
//    return state_buttons;
//}


void widget_modelset::remove_tree_items(QTreeWidgetItem* _main_item)
{
    QList<QTreeWidgetItem*> list_children =_main_item->takeChildren();
    for (int ii=0;ii<list_children.size() ;++ii )
    {
        QList<QTreeWidgetItem*> list_grandchildren =
                list_children.at(ii)->takeChildren();
        for (int jj=0;jj<list_grandchildren.size() ;++jj )
        {
            QList<QTreeWidgetItem*> list_grandgrandchildren =
                    list_grandchildren.at(jj)->takeChildren();
            for (int kk=0;kk<list_grandgrandchildren.size() ;++kk )
            {
                item_pbu->removeChild(list_grandgrandchildren.at(kk));
            }
            item_pbu->removeChild(list_grandchildren.at(jj));
        }
        item_pbu->removeChild(list_children.at(ii));
    }
}

void widget_modelset::add_basic_items_la(QTreeWidgetItem* _item, int _count)
{
    QList<QString> list;
    QString buff = input_dialog_model(state_la);
//    QSqlQuery query(db);
//    QString select = "SELECT nx_max, ny_max, nx_min, m_max, "
//                     "practical_roof FROM aircrafts WHERE ID = "+buff;
//    query.exec(select);

//    while (query.next())
//    {
        list<<"ID: "+QString::number(_count)
           <<"Модель: "+buff;
//          <<"nx_max: "+query.value(0).toString()
//         <<"ny_max: "+query.value(1).toString()
//        <<"nx_min: "+query.value(2).toString()
//        <<"m_max: "+query.value(3).toString()
//        <<"practical_roof: "+query.value(4).toString();
//    }
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         _item->addChild(item_child);
         item_child->setText(0,list.at(ii));
         vector_data_la.append(list.at(ii).split(": ").at(1));
    }
}

void widget_modelset::add_children_items_pu(double x, double y)
{
    int count = vector_item_pu.size();
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QList<QString> list, list_buff;
    list<<"ID: "+QString::number(count)
        <<"x: "+QString::number(x)
        <<"y: "+QString::number(y)
        <<"z: 0";
    list_buff=input_dialog_pu();
    list.append(list_buff);
    vector_item_pu.append(item);
    top_item_pu->addChild(item);
    item->setText(0, "ПУ_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
         vector_data_pu.append(list.at(ii).split(": ").at(1));
    }
}

void widget_modelset::add_children_items_radar(double x, double y)
{
    int count = vector_item_radar.size();
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QList<QString> list;
    list<<"ID: "+QString::number(count)
        <<"Модель: "
        <<"x: "+QString::number(x)
        <<"y: "+QString::number(y)
        <<"z: 0";
    list[1]+=input_dialog_model(state_radar);
    list.append(input_dialog_radar());

    vector_item_radar.append(item);
    top_item_radar->addChild(item);
    item->setText(0, "РЛС_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
         vector_data_radar.append(list.at(ii).split(": ").at(1));
    }
}

void widget_modelset::add_children_items_la(double x, double y,
                                            QTreeWidgetItem* _item)
{
    QVector<QString> vector = input_dialog_point_la();

    QList<QString> list;
    list<< "#"+QString::number(vector_x_la.size())
        <<"x: "+QString::number(x)
        <<"y: "+QString::number(y)
        <<"z: "+vector.at(0)
        <<"Скорость: "+vector.at(1);
    QTreeWidgetItem* item_child = new QTreeWidgetItem();
    _item->addChild(item_child);
    item_child->setText(0,list.at(0));    
    for (int ii=1;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_grandchild = new QTreeWidgetItem();
         item_child->addChild(item_grandchild);
         item_grandchild->setText(0,list.at(ii));
         vector_data_la.append(list.at(ii).split(": ").at(1));
    }
}

QVector<QString> widget_modelset::input_dialog_point_la()
{
    QVector<QString> results;
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    d->setWindowTitle("Введите данные");
    QLineEdit* lineEdit_z = new QLineEdit();
    QLineEdit* lineEdit_velocity = new QLineEdit();
    QLabel* label_z = new QLabel("z");
    QLabel* label_velocity = new QLabel("Скорость");
    QLabel* label_point = new QLabel("Point #"+
                                     QString::number(vector_x_la.size()));

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    lineEdit_z->setValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]*[.,]?"
                                        "[0-9]+(?:[eE][-+]?[0-9]+)?$"), this));
    lineEdit_velocity->
            setValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]*[.,]?[0-9]+"
                                            "(?:[eE][-+]?[0-9]+)?$"), this));
    vbox->addWidget(label_point);
    vbox->addWidget(label_z);
    vbox->addWidget(lineEdit_z);
    vbox->addWidget(label_velocity);
    vbox->addWidget(lineEdit_velocity);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    int result=0;
    while ((lineEdit_z->text()==NULL)||(lineEdit_velocity->text()==NULL))
         result = d->exec();
    if(result == QDialog::Accepted)
    {
        results.append(lineEdit_z->text());
        results.append(lineEdit_velocity->text());
    }
    return results;
}


QString widget_modelset::input_dialog_model(int _state)
{
    QString str;
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    d->setWindowTitle("Введите данные");
    QComboBox* comboBox = new QComboBox();
    QLabel* label = new QLabel();

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    QSqlQuery query(db);
    QStringList str_list;
    if (_state==state_la)
    {
        QString select = "SELECT ID, type FROM aircrafts WHERE type = 'ЛА'";
        query.exec(select);
        label->setText("Выберите модель для ЛА_"+
                       QString::number(vector_x_la.size()));
    }
    if (_state==state_radar)
    {
        QString select = "SELECT ID FROM radars";
        query.exec(select);
        label->setText("Выберите модель для РЛС_"+
                       QString::number(vector_item_radar.size()));
    }

    while (query.next())
    {
       str_list << query.value(0).toString();
    }
    comboBox->addItems(str_list);

    vbox->addWidget(label);
    vbox->addWidget(comboBox);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        return str=comboBox->currentText();
    }
    return "0";
}

QList<QString> widget_modelset::input_dialog_radar()
{
    QList<QString> results;
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    d->setWindowTitle("Введите данные");
    QLineEdit* lineEdit_radius = new QLineEdit();
    QLineEdit* lineEdit_targets = new QLineEdit();
    QLineEdit* lineEdit_sopr = new QLineEdit();
    QLabel* label_radius = new QLabel("Радиус действия (км):");
    QLabel* label_targets =
            new QLabel("Количество каналов сопровождения целей:");
    QLabel* label_sopr = new QLabel("Количество каналов сопровождения ЗУР:");
    QLabel* label_point = new QLabel("РЛС_"+
                                     QString::number(vector_item_radar.size()));

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    lineEdit_radius->setValidator(new QRegExpValidator(QRegExp("^[0-9]*[.,]?"
                                        "[0-9]+(?:[eE][-+]?[0-9]+)?$"), this));
    lineEdit_targets->
            setValidator(new QRegExpValidator(QRegExp("^[0-9]*[.,]?[0-9]+"
                                            "(?:[eE][-+]?[0-9]+)?$"), this));
    lineEdit_sopr->setValidator(new QRegExpValidator(QRegExp("^[0-9]*[.,]?"
                                        "[0-9]+(?:[eE][-+]?[0-9]+)?$"), this));

    lineEdit_radius->setText("100");
    lineEdit_targets->setText("64");
    lineEdit_sopr->setText("32");

    vbox->addWidget(label_point);
    vbox->addWidget(label_radius);
    vbox->addWidget(lineEdit_radius);
    vbox->addWidget(label_targets);
    vbox->addWidget(lineEdit_targets);
    vbox->addWidget(label_sopr);
    vbox->addWidget(lineEdit_sopr);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    int result=0;
//    while ( (lineEdit_cooldown->text()==NULL)||
//            (lineEdit_count->text()==NULL) ||
//            (lineEdit_radius->text()==NULL) )
         result = d->exec();
    if(result == QDialog::Accepted)
    {
        results.append("Радиус действия (км): "+lineEdit_radius->text());
        results.append("Количество каналов сопровождения целей: "
                        +lineEdit_targets->text());
        results.append("Количество каналов сопровождения ЗУР: "
                        +lineEdit_sopr->text());
    }
    return results;
}

QList<QString> widget_modelset::input_dialog_pu()
{
    QList<QString> results;
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    d->setWindowTitle("Введите данные");
    QLineEdit* lineEdit_radius = new QLineEdit();
    QLineEdit* lineEdit_count = new QLineEdit();
    QLineEdit* lineEdit_cooldown = new QLineEdit();
    QLabel* label_radius = new QLabel("Радиус действия (км):");
    QLabel* label_count = new QLabel("Количество ЗУР:");
    QLabel* label_cooldown = new QLabel("Время перезарядки (c):");
    QLabel* label_point = new QLabel("ПУ_"+
                                     QString::number(vector_item_pu.size()));

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    lineEdit_radius->setValidator(new QRegExpValidator(QRegExp("^[0-9]*[.,]?"
                                        "[0-9]+(?:[eE][-+]?[0-9]+)?$"), this));
    lineEdit_count->
            setValidator(new QRegExpValidator(QRegExp("^[0-9]*[.,]?[0-9]+"
                                            "(?:[eE][-+]?[0-9]+)?$"), this));
    lineEdit_cooldown->setValidator(new QRegExpValidator(QRegExp("^[0-9]*[.,]?"
                                        "[0-9]+(?:[eE][-+]?[0-9]+)?$"), this));

    lineEdit_radius->setText("100");
    lineEdit_count->setText("8");
    lineEdit_cooldown->setText("10");

    vbox->addWidget(label_point);
    vbox->addWidget(label_radius);
    vbox->addWidget(lineEdit_radius);
    vbox->addWidget(label_count);
    vbox->addWidget(lineEdit_count);
    vbox->addWidget(label_cooldown);
    vbox->addWidget(lineEdit_cooldown);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    int result=0;
//    while ( (lineEdit_cooldown->text()==NULL)||
//            (lineEdit_count->text()==NULL) ||
//            (lineEdit_radius->text()==NULL) )
         result = d->exec();
    if(result == QDialog::Accepted)
    {
        results.append("Радиус действия (км): "+lineEdit_radius->text());
        results.append("Количество ЗУР: "+lineEdit_count->text());
        results.append("Время перезарядки (c): "+lineEdit_cooldown->text());
    }
    return results;
}

void widget_modelset::on_save_pushButton_clicked()
{
    set_state_buttons(777);
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    d->setWindowTitle("Сохранить");
    QLineEdit* lineEdit_name = new QLineEdit();
    QLabel* label_name = new QLabel("Введите имя:");

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|
                                                       QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    struct tm newtime;
    time_t ltime;
    //char buf[50];
    ltime = time(&ltime);
    localtime_r(&ltime, &newtime);

    QString name = QDateTime::currentDateTime().toString("MM-dd-hh");
    lineEdit_name->setText(name);

    vbox->addWidget(label_name);
    vbox->addWidget(lineEdit_name);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    int result=0;
    result = d->exec();
    if(result == QDialog::Accepted)
    {
        name=lineEdit_name->text() + "_config.csv";
        name_config = name.toStdString().c_str();
        fill_config("pbu",1,4,vector_data_pbu,name);
        fill_config("pu",vector_item_pu.size(),7,vector_data_pu,name);
        fill_config("rls",vector_item_radar.size(),8,vector_data_radar,name);
        fill_config_for_la("la",vector_data_la_all.size(),name);
    }
}

// как параметры передаем число объектов каждого типа,
//число параметров данного объекта и затем их параметры массивом
void widget_modelset::fill_config(QString type_object,
                                  int num_objects,
                                  int num_params,
                                  QVector <QString> params,
                                  QString config_name)
{
    // указатель файла
    QFile file(config_name);
    // открывает существующий CSV-файл или создает новый файл.
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream writeStream(&file);
        writeStream << type_object << "\n"
                    << num_objects << "\n";
        // Цикл по объектам текущего типа
        for (int i = 0; i < num_objects; i++)
        {
            // Вставляем данные в файл
            for (int j = 0; j < num_params - 1; j++)
            {
                writeStream << params.at(i*num_params + j) << ", ";
            }
            writeStream << params.at(i*num_params + num_params - 1) << "\n";
        }
        file.close();
    }
}

void widget_modelset::fill_config_for_la(QString type_object,
                                         int num_objects,
                                         QString config_name)
{
    int num_params;
    QVector <QString> params;
    // указатель файла
    QFile file(config_name);
    // открывает существующий CSV-файл или создает новый файл.
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream writeStream(&file);
        writeStream << type_object << "\n"
                    << num_objects << "\n";
    // Цикл по объектам текущего типа
    for (int i = 0; i < num_objects; i++)
    {
        num_params = vector_data_la_all.at(i).size();
        params = vector_data_la_all.at(i);
        // Вставляем данные в файл
        for (int j = 0; j < num_params - 1; j++)
        {
            writeStream << params.at(j) << ", ";
        }
        writeStream << params.at(num_params - 1) << "\n";
    }
    file.close();
    }
}
//void widget_modelset::add_maneuver(QMouseEvent *_event)
//{
//    flag_maneuver = true;
//    QString cord;
//    double x = ui->customPlot->xAxis->pixelToCoord(_event->pos().x());
//    double y = ui->customPlot->yAxis->pixelToCoord(_event->pos().y());
//    cord = "x = "+QString::number(x)+", y = "+QString::number(y);
//    ui->lineEdit->setText(cord);
//    add_point(x,y);
//}
