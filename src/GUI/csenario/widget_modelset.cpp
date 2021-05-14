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
    ui->pushButton_aircraft->setCheckable(true);
    ui->pushButton_pu->setCheckable(true);
    ui->pushButton_pbu->setCheckable(true);

    connect(ui->pushButton_radar, SIGNAL(toggled(bool)),
            this, SLOT(button_radar_toggled(bool)));
    connect(ui->pushButton_aircraft, SIGNAL(toggled(bool)),
            this, SLOT(button_aircraft_toggled(bool)));
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

    top_item_aircraft = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_aircraft);
    top_item_aircraft->setText(0,"ЛА");

}

widget_modelset::~widget_modelset()
{
    delete ui;
}

void widget_modelset::clearData()
{
    vector_x_radar.clear();
    vector_y_radar.clear();
    vector_x_aircraft.clear();
    vector_y_aircraft.clear();
    vector_x_pu.clear();
    vector_y_pu.clear();

    vector_item_aircraft.clear();
    vector_item_radar.clear();
    vector_item_pu.clear();
    vector_item_pbu.clear();

    vector_data_aircraft.clear();
    vector_data_pbu.clear();
    vector_data_pu.clear();
    vector_data_radar.clear();
    vector_data_aircraft_all.clear();

    vector_aircrafts.clear();
    vector_launchers.clear();
    vector_radars.clear();

    x_pbu.clear();
    y_pbu.clear();

    ccp_pbu.clearData();

    name_config.clear();
    remove_tree_items();
    index_aircraft=0;
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    ui->customPlot->update();
    create_stationary_elements();
    set_state_buttons(777);
    count_id=0;
    ui->label_name_config->clear();
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
    case state_aircraft:
    {
        add_point(x,y);
        plot(index_aircraft, vector_x_aircraft, vector_y_aircraft);
        if (item_aircraft_added==false)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            int count = vector_item_aircraft.size();
            top_item_aircraft->addChild(item);
            item->setText(0, "ЛА_"+QString::number(count));
            add_basic_items_aircraft(item);
            add_children_items_aircraft(x, y,item);
            vector_item_aircraft.append(item);
            item_aircraft_added = true;
        }
        else
        {
            add_children_items_aircraft(x, y, vector_item_aircraft.last());
        }
    }break;
    case state_pbu:
    {
        add_point(x,y);
        plot(state_pbu, x_pbu, y_pbu);
        vector_data_pbu.clear();
        for (QTreeWidgetItem* it : vector_item_pbu)
            top_item_pbu->removeChild(it);
        ccp_pbu.set_id(0);
        ccp_pbu.set_coordinates(x,y,0);

        QList<QString> list;
        list<<"ID: 0"
            <<"x: "+QString::number(x)
            <<"y: "+QString::number(y)
            <<"z: 0";
        for (int ii=0;ii<list.size() ; ++ii)
        {
             item_pbu=new QTreeWidgetItem();
             item_pbu->setText(0,list.at(ii));
             vector_item_pbu.append(item_pbu);
             vector_data_pbu.append(list.at(ii).split(": ").at(1));
             top_item_pbu->addChild(item_pbu);
        }
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
    case state_aircraft:
    {
        vector_x_aircraft.append(x);
        vector_y_aircraft.append(y);
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

void widget_modelset::button_aircraft_toggled(bool state)
{
    if(state==true)//Кнопка зажата
    {
        set_state_buttons(state_aircraft);
        ui->customPlot->addGraph();
        index_aircraft = (ui->customPlot->graphCount())-1;
        vector_x_aircraft.clear();
        vector_y_aircraft.clear();
        QPen pen_line(Qt::red, 3, Qt::DashDotLine,
                 Qt::RoundCap, Qt::RoundJoin);
        QColor color( qrand() % ((255 + 1) - 0) + 0,
                      qrand() % ((255 + 1) - 0) + 0,
                      qrand() % ((255 + 1) - 0) + 0, 255 );
        pen_line.setColor(color);
        ui->customPlot->graph(index_aircraft)->
                setScatterStyle(QCPScatterStyle::ssCircle);
        ui->customPlot->graph(index_aircraft)->setLineStyle(QCPGraph::lsLine);
        ui->customPlot->graph(index_aircraft)->setPen(pen_line);
//        connect(ui->customPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)),
//                this, SLOT(add_maneuver(QMouseEvent*)));
        connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
    }
    else//Кнопка отжата
    {
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
                this, SLOT(click_on_canvas(QMouseEvent*)));
        item_aircraft_added = false;
        vector_data_aircraft_all.append(vector_data_aircraft);
        vector_data_aircraft.clear();
    }
}


void widget_modelset::set_state_buttons(int state)
{
    state_buttons = state;
    switch (state)
    {
    case state_aircraft:
    {
       ui->pushButton_pbu->setChecked(false);
       ui->pushButton_pu->setChecked(false);
       ui->pushButton_radar->setChecked(false);
    }break;
    case state_pbu:
    {
        ui->pushButton_aircraft->setChecked(false);
        ui->pushButton_pu->setChecked(false);
        ui->pushButton_radar->setChecked(false);
    }break;
    case state_pu:
    {
        ui->pushButton_aircraft->setChecked(false);
        ui->pushButton_pbu->setChecked(false);
        ui->pushButton_radar->setChecked(false);
    }break;
    case state_radar:
    {
        ui->pushButton_aircraft->setChecked(false);
        ui->pushButton_pu->setChecked(false);
        ui->pushButton_pbu->setChecked(false);
    }break;
    default:
    {
        ui->pushButton_aircraft->setChecked(false);
        ui->pushButton_pbu->setChecked(false);
        ui->pushButton_pu->setChecked(false);
        ui->pushButton_radar->setChecked(false);
    }break;
    }
}

void widget_modelset::on_pushButton_clear_clicked()
{
    clearData();
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


void widget_modelset::remove_tree_items()
{
    ui->treeWidget->clear();
    top_item_pbu = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_pbu);
    top_item_pbu->setText(0,"ПБУ");

    top_item_radar = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_radar);
    top_item_radar->setText(0,"РЛС");

    top_item_pu = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_pu);
    top_item_pu->setText(0,"ПУ");

    top_item_aircraft = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_aircraft);
    top_item_aircraft->setText(0,"ЛА");

}

void widget_modelset::add_basic_items_aircraft(QTreeWidgetItem* _item)
{
    ++count_id;
    QList<QString> list;
    QString buff = input_dialog_model(state_aircraft);
    QSqlQuery query(db);
    QString select = "SELECT nx_max, ny_max, nx_min, m_max, "
                     "practical_roof FROM aircrafts WHERE type_name = '"+buff+"'";

    if(!query.exec(select))
    {
        qDebug()<<query.lastError()<<"select aircraft";
    }

    Aircraft *craft = new Aircraft();
    craft->set_id(count_id);
    craft->set_model(buff);
    craft->set_name("plane_"+
                    QString::number(vector_aircrafts.size()));

    while (query.next())
    {
        list<<"ID: "+QString::number(count_id)/*QString::number(_count)*/
           <<"Модель: "+buff
          <<"max_Nx: "+query.value(0).toString()
         <<"max_Ny: "+query.value(1).toString()
        <<"min_Nx: "+query.value(2).toString()
        <<"max_M: "+query.value(3).toString()
        <<"practical_roof: "+query.value(4).toString();        
    }
        craft->set_properties(list.at(2).split(": ").at(1).toDouble(),
                              list.at(3).split(": ").at(1).toDouble(),
                              list.at(4).split(": ").at(1).toDouble(),
                              list.at(5).split(": ").at(1).toDouble(),
                              list.at(6).split(": ").at(1).toDouble());


    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         _item->addChild(item_child);
         item_child->setText(0,list.at(ii));
         vector_data_aircraft.append(list.at(ii).split(": ").at(1));
    }
    vector_aircrafts.append(craft);
}

void widget_modelset::add_children_items_pu(double x, double y)
{
    ++count_id;
    int count = vector_item_pu.size();

    Launcher* pu = new Launcher();
    vector_launchers.append(pu);
    vector_launchers.last()->set_id(count_id);
    vector_launchers.last()->set_coordinates(x,y,0);
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QList<QString> list, list_buff;
    list<<"ID: "+QString::number(count_id)
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
    ++count_id;
    int count = vector_item_radar.size();
    QTreeWidgetItem* item = new QTreeWidgetItem();

    QString str = input_dialog_model(state_radar);

    Radar *rls = new Radar();
    rls->set_coordinates(x,y,0);
    rls->set_id(count_id);
    rls->set_model(str.toInt());
    vector_radars.append(rls);


    QList<QString> list;
    list<<"ID: "+QString::number(count_id)
        <<"Модель: "
        <<"x: "+QString::number(x)
        <<"y: "+QString::number(y)
        <<"z: 0";
    list[1]+=str;

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
    //qDebug()<<vector_data_radar;
}

void widget_modelset::add_children_items_aircraft(double x, double y,
                                            QTreeWidgetItem* _item)
{
    QVector<QString> vector = input_dialog_point_aircraft();

    Point point;
    point.set_coordinates(x,y,vector.at(0).toDouble());
    point.set_velocity(vector.at(1).toDouble());

    vector_aircrafts.last()->append_point(point);

    QList<QString> list;
    list<<"#"+QString::number(vector_x_aircraft.size())
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
         vector_data_aircraft.append(list.at(ii).split(": ").at(1));
    }
}

QVector<QString> widget_modelset::input_dialog_point_aircraft()
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
                                     QString::number(vector_x_aircraft.size()));

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
    if (_state==state_aircraft)
    {
        QString select = "SELECT type_name,ID, type FROM aircrafts WHERE type = 'ЛА'";
        query.exec(select);
        label->setText("Выберите модель для ЛА_"+
                       QString::number(vector_data_aircraft_all.size()));
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
    QLineEdit* lineEdit_rotate_x = new QLineEdit();
    QLineEdit* lineEdit_rotate_y = new QLineEdit();
    QLineEdit* lineEdit_rotate_z = new QLineEdit();
    QLabel* label_radius = new QLabel("Радиус действия (км):");
    QLabel* label_targets =
            new QLabel("Количество каналов сопровождения целей:");
    QLabel* label_sopr = new QLabel("Количество каналов сопровождения ЗУР:");
    QLabel* label_point = new QLabel("РЛС_"+
                                     QString::number(vector_item_radar.size()));
    QLabel* label_rotate_x =
            new QLabel("Направление оси вращения РЛС _X: ");
    QLabel* label_rotate_y =
            new QLabel("Направление оси вращения РЛС _Y: ");
    QLabel* label_rotate_z =
            new QLabel("Направление оси вращения РЛС _Z: ");


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
    lineEdit_rotate_x->setText("0");
    lineEdit_rotate_y->setText("0");
    lineEdit_rotate_z->setText("0");

    vbox->addWidget(label_point);
    vbox->addWidget(label_radius);
    vbox->addWidget(lineEdit_radius);
    vbox->addWidget(label_targets);
    vbox->addWidget(lineEdit_targets);
    vbox->addWidget(label_sopr);
    vbox->addWidget(lineEdit_sopr);
    vbox->addWidget(label_rotate_x);
    vbox->addWidget(lineEdit_rotate_x);
    vbox->addWidget(label_rotate_y);
    vbox->addWidget(lineEdit_rotate_y);
    vbox->addWidget(label_rotate_z);
    vbox->addWidget(lineEdit_rotate_z);
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
        results.append("Направление оси вращения РЛС _X: "+
                       lineEdit_rotate_x->text());
        results.append("Направление оси вращения РЛС _Y: "+
                       lineEdit_rotate_y->text());
        results.append("Направление оси вращения РЛС _Z: "+
                       lineEdit_rotate_z->text());
        vector_radars.last()->set_properties(lineEdit_targets->text().toInt(),
                                             lineEdit_sopr->text().toInt(),
                                             lineEdit_radius->text().toDouble());
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
    lineEdit_count->setText("4");
    lineEdit_cooldown->setText("10");

    vbox->addWidget(label_point);
    vbox->addWidget(label_radius);
    vbox->addWidget(lineEdit_radius);
    vbox->addWidget(label_count);
    vbox->addWidget(lineEdit_count);
    vbox->addWidget(label_cooldown);
    vbox->addWidget(lineEdit_cooldown);
    vbox->addWidget(buttonBox);

    lineEdit_count->setEnabled(false);

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
        vector_launchers.last()->set_properties(lineEdit_radius->text().toDouble(),
                                             lineEdit_count->text().toInt(),
                                             lineEdit_cooldown->text().toDouble());
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
    ///@note добавить обработку пустых векторов
    if(result == QDialog::Accepted)
    {
        QMessageBox msgBox;
        name=lineEdit_name->text() + "_config.json";
        name_config = name.toStdString().c_str();
        serialization_json(name);
        ui->label_name_config->setText(name);
//        fill_csv("pbu",1,4,vector_data_pbu,name);
//        fill_csv("pu",vector_item_pu.size(),7,vector_data_pu,name);
//        fill_csv("rls",vector_item_radar.size(),8,vector_data_radar,name);
//        fill_csv_for_la("la",vector_data_aircraft_all.size(),name);

        msgBox.setText("Данные сохранены в файл: "+name);
        msgBox.exec();
    }
}

//void widget_modelset::fill_csv(QString type_object,
//                                  int num_objects,
//                                  int num_params,
//                                  QVector <QString> params,
//                                  QString config_name)
//{
//    QFile file(config_name);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
//    {
//        QTextStream writeStream(&file);
//        writeStream << type_object << "\n"
//                    << num_objects << "\n";
//        for (int i = 0; i < num_objects; i++)
//        {
//            for (int j = 0; j < num_params - 1; j++)
//            {
//                writeStream << params.at(i*num_params + j) << ", ";
//            }
//            writeStream << params.at(i*num_params + num_params - 1) << "\n";
//        }
//        file.close();
//    }
//}

//void widget_modelset::fill_csv_for_la(QString type_object,
//                                      int num_objects,
//                                      QString config_name)
//{
//    int num_params;
//    QVector <QString> params;

//    QFile file(config_name);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
//    {
//        QTextStream writeStream(&file);
//        writeStream << type_object << "\n"
//                    << num_objects << "\n";

//    for (int i = 0; i < num_objects; i++)
//    {
//        num_params = vector_data_aircraft_all.at(i).size();
//        params = vector_data_aircraft_all.at(i);

//        for (int j = 0; j < num_params - 1; j++)
//        {
//            writeStream << params.at(j) << ", ";
//        }
//        writeStream << params.at(num_params - 1) << "\n";
//    }
//    file.close();
//    }
//}

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

void widget_modelset::serialization_json(QString _config_name)
{
    QFile fileJson(_config_name);
    fileJson.open(QIODevice::WriteOnly);
    QJsonArray objArray;
    QJsonObject rootJsonObj
    {
        {"scenario_name",   _config_name.split(".").at(0)},
        {"end_time",        ui->time_modelinglineEdit->text()},
    };

    objArray.append(ccp_pbu.toJsonObject());
    for(Radar* rls_count : vector_radars)
    {
        objArray.append(rls_count->toJsonObject());
    }

    for(Aircraft* plane_count : vector_aircrafts)
    {
        objArray.append(plane_count->toJsonObject());
    }

    for(Launcher* launcher_count : vector_launchers)
    {
        objArray.append(launcher_count->toJsonObject());
    }

//    QVector<Radar> v_radars;
//    CombatControlPoint *pbu = new CombatControlPoint();
//    QVector<Aircraft> v_aircraft;
//    QVector<Launcher> v_launcher;
//    v_radars.append(Radar());v_radars.append(Radar());v_radars.append(Radar());v_radars.append(Radar());
//    v_launcher.append(Launcher());v_launcher.append(Launcher());v_launcher.append(Launcher());
//    v_aircraft.append(Aircraft());v_aircraft.append(Aircraft());
//    for (Launcher l : v_launcher)
//    {
//        objArray.append(l.toJsonObject());
//    }
//    for (Aircraft air : v_aircraft)
//    {
//        objArray.append(air.toJsonObject());
//    }
//    for (Radar r : v_radars)
//    {
//        objArray.append(r.toJsonObject());
//    }
//    objArray.append(pbu->toJsonObject());

    rootJsonObj.insert("objects",QJsonValue(objArray));

    fileJson.write(QJsonDocument(rootJsonObj).toJson());
    fileJson.close();
}

//void widget_modelset::serialization_json(QString _config_name)
//{
//    QFile fileJson(_config_name);
//    fileJson.open(QIODevice::WriteOnly);

//    QJsonArray objArray;
//    QJsonObject rootJsonObj
//    {
//        {"scenario_name",   _config_name.split(".").at(0)},
//        {"end_time",        ui->time_modelinglineEdit->text()},
//    };
//    //==========================================================================
//    //  Упаковка данных ПБУ
//    QJsonObject pbuJsonObj
//    {
//        {"id", vector_data_pbu.at(0)},
//        {"model_name", "pbu"}
//    };
//    QJsonObject pbuJsonInitData
//    {
//        //{"id", vector_data_pbu.at(0)},
//        {"x",vector_data_pbu.at(1)},
//        {"y",vector_data_pbu.at(2)},
//        {"z",vector_data_pbu.at(3)},
//    };
//    pbuJsonObj.insert("initial_data", QJsonValue(pbuJsonInitData));
//    objArray.append(QJsonValue(pbuJsonObj));
//    //==========================================================================
//    //  Упаковка данных ПУ
//    for(int ii = 0; ii<vector_data_pu.size(); ii+=7)
//    {
//        QJsonObject puJsonObj
//        {
//            {"id", vector_data_pu.at(ii)},
//            {"model_name", "pu"}
//        };
//        QJsonObject puJsonInitData
//        {
//            //{"id", vector_data_pu.at(ii)},
//            {"x",vector_data_pu.at(1+ii)},
//            {"y",vector_data_pu.at(2+ii)},
//            {"z",vector_data_pu.at(3+ii)},
//            {"radius",vector_data_pu.at(4+ii)},
//            {"count_ammo",vector_data_pu.at(5+ii)},
//            {"cooldown",vector_data_pu.at(6+ii)}
//        };
//        puJsonObj.insert("initial_data", QJsonValue(puJsonInitData));
//        objArray.append(QJsonValue(puJsonObj));
//    }
//    //==========================================================================
//    //  Упаковка данных РЛС
//    for(int ii = 0; ii<vector_data_radar.size(); ii+=11)
//    {
//        QJsonObject rlsJsonObj
//        {
//            {"id", vector_data_radar.at(ii)},
//            {"model_name", "rls"}
//        };
//        QJsonObject rlsJsonInitData
//        {
//           // {"id", vector_data_radar.at(ii)},
//            {"model", vector_data_radar.at(1+ii)},
//            {"x",vector_data_radar.at(2+ii)},
//            {"y",vector_data_radar.at(3+ii)},
//            {"z",vector_data_radar.at(4+ii)},
//            {"radius",vector_data_radar.at(5+ii)},
//            {"count_channels_targets",vector_data_radar.at(6+ii)},
//            {"count_channels_zurs",vector_data_radar.at(7+ii)},
//            {"rotate_x",vector_data_radar.at(8+ii)},
//            {"rotate_y",vector_data_radar.at(9+ii)},
//            {"rotate_z",vector_data_radar.at(10+ii)}
//        };
//        rlsJsonObj.insert("initial_data", QJsonValue(rlsJsonInitData));
//        objArray.append(QJsonValue(rlsJsonObj));
//    }
//    //==========================================================================
//    //  Упаковка данных ЛА
//    for(QVector<QString> vector_la : vector_data_aircraft_all)
//    {
//        QJsonObject laJsonObj
//        {
//            {"id", vector_la.at(0)},
//            {"model_name", "AirTarget"}
//        };

//        QJsonObject laJsonInitData
//        {
//            //{"id", vector_la.at(0)},
//            {"target_name", "plane_"+vector_la.at(0)},
//            //{"target_model_type", vector_la.at(1)},
//            {"target_model_type", "Fighter"},
//            {"target_max_Nx",vector_la.at(2)},
//            {"target_max_Ny",vector_la.at(3)},
//            {"target_min_Nx",vector_la.at(4)},
//            {"target_max_M",vector_la.at(5)},
//            {"target_practical_roof",vector_la.at(6)}
//        };
//        QJsonArray la_points;
//       // int count = 1;
//        for(int ii = 7; ii<vector_la.size(); ii+=4)
//        {
//            QJsonObject j_object_point
//            {
//                //{"point", count++},
//                {"x", vector_la.at(ii)},
//                {"y", vector_la.at(ii+1)},
//                {"z",vector_la.at(ii+2)},
//                {"vel",vector_la.at(ii+3)}
//            };
//            la_points.append(j_object_point);
//        }
//        laJsonInitData.insert("target_points", QJsonValue(la_points));
//        laJsonObj.insert("initial_data", QJsonValue(laJsonInitData));
//        objArray.append(laJsonObj);
//    }
//    //==========================================================================
//    rootJsonObj.insert("objects",QJsonValue(objArray));

//    fileJson.write(QJsonDocument(rootJsonObj).toJson());
//    fileJson.close();
//}
///@note переделать
void widget_modelset::deserialization_json(QString _config_name)
{
    QFile fileJson(_config_name);
    fileJson.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(fileJson.readAll());
    QJsonObject j_object = doc.object();

    QString name = j_object["scenario_name"].toString();
    ui->time_modelinglineEdit->setText(j_object["end_time"].toString());

    vector_data_pbu.append(j_object["pbu"].toObject()["id"].toString());
    vector_data_pbu.append(j_object["pbu"].toObject()["x"].toString());
    vector_data_pbu.append(j_object["pbu"].toObject()["y"].toString());
    vector_data_pbu.append(j_object["pbu"].toObject()["z"].toString());

    QJsonArray array_pu = j_object["pu"].toArray();
    for (QJsonValue value : array_pu)
    {
        vector_data_pu.append(value.toObject()["id"].toString());
        vector_data_pu.append(value.toObject()["x"].toString());
        vector_data_pu.append(value.toObject()["y"].toString());
        vector_data_pu.append(value.toObject()["z"].toString());
        vector_data_pu.append(value.toObject()["radius"].toString());
        vector_data_pu.append(value.toObject()["count_ammo"].toString());
        vector_data_pu.append(value.toObject()["cooldown"].toString());
    }

    QJsonArray array_rls = j_object["rls"].toArray();
    for (QJsonValue value : array_rls)
    {
        vector_data_radar.append(value.toObject()["id"].toString());
        vector_data_radar.append(value.toObject()["model"].toString());
        vector_data_radar.append(value.toObject()["x"].toString());
        vector_data_radar.append(value.toObject()["y"].toString());
        vector_data_radar.append(value.toObject()["z"].toString());
        vector_data_radar.append(value.toObject()["radius"].toString());
        vector_data_radar.append(value.toObject()["count_channels_targets"]
                                                                   .toString());
        vector_data_radar.append(value.toObject()["count_channels_zurs"]
                                                                   .toString());
    }

    QJsonArray array_la = j_object["la"].toArray();
    for (QJsonValue value : array_la)
    {
        QVector<QString> vector;
        vector.append(value.toObject()["id"].toString());
        vector.append(value.toObject()["target_model_type"].toString());
        vector.append(value.toObject()["target_max_Nx"].toString());
        vector.append(value.toObject()["target_max_Ny"].toString());
        vector.append(value.toObject()["target_min_Nx"].toString());
        vector.append(value.toObject()["target_max_M"].toString());
        vector.append(value.toObject()["target_practical_roof"].toString());
        QJsonArray array_points = value.toObject()["target_points"].toArray();
        for (QJsonValue point : array_points)
        {
            vector.append(point.toObject()["x"].toString());
            vector.append(point.toObject()["y"].toString());
            vector.append(point.toObject()["z"].toString());
            vector.append(point.toObject()["vel"].toString());
        }
        vector_data_aircraft_all.append(vector);
    }
    fileJson.close();
}

void widget_modelset::on_pushButton_open_clicked()
{
    const QString& title = QString::fromUtf8("Выберите кофигурационный файл");
    const QString& path   = qApp->applicationDirPath();
    const QString& filters = QString::fromUtf8("Файлы регистрации (*.json)");
    QString filename = QFileDialog::getOpenFileName(this, title, path, filters);

    ui->label_name_config->setText(filename);

    if(filename.isEmpty())
        return;

    clearData();
    deserialization_json(filename);
}



//QFile fileJson(_config_name);
//QString scenario_name = _config_name.split(".").at(0);
//QJsonObject j_object
//{
//    {"scenario_name", scenario_name},
//    {"end_time",ui->time_modelinglineEdit->text()},
//};

//fileJson.open(QIODevice::WriteOnly);

//QJsonObject j_oblect_pbu
//{
//    {"id", vector_data_pbu.at(0)},
//    {"model_name", "pbu"},
//    {"x",vector_data_pbu.at(1)},
//    {"y",vector_data_pbu.at(2)},
//    {"z",vector_data_pbu.at(3)},
//};

//QJsonArray array_pu;
//for(int ii = 0; ii<vector_data_pu.size(); ii+=7)
//{
//    QJsonObject j_object_pu
//    {
//        {"id", vector_data_pu.at(ii)},
//        {"x",vector_data_pu.at(1+ii)},
//        {"y",vector_data_pu.at(2+ii)},
//        {"z",vector_data_pu.at(3+ii)},
//        {"radius",vector_data_pu.at(4+ii)},
//        {"count_ammo",vector_data_pu.at(5+ii)},
//        {"cooldown",vector_data_pu.at(6+ii)}
//    };
//    array_pu.append(QJsonValue(j_object_pu));
//}

//QJsonArray array_radar;
//for(int ii = 0; ii<vector_data_radar.size(); ii+=8)
//{
//    QJsonObject j_object_radar
//    {
//        {"id", vector_data_radar.at(ii)},
//        {"model", vector_data_radar.at(1+ii)},
//        {"x",vector_data_radar.at(2+ii)},
//        {"y",vector_data_radar.at(3+ii)},
//        {"z",vector_data_radar.at(4+ii)},
//        {"radius",vector_data_radar.at(5+ii)},
//        {"count_channels_targets",vector_data_radar.at(6+ii)},
//        {"count_channels_zurs",vector_data_radar.at(7+ii)}
//    };
//    array_radar.append(QJsonValue(j_object_radar));
//}

//QJsonArray array_la_all;
//////fix
//int count_la=0;
//for(QVector<QString> vector_la : vector_data_aircraft_all)
//{
//    QJsonObject j_object_la
//    {
//        {"id", vector_la.at(0)},
//        {"target_name", "plane_"+QString::number(++count_la)},
//        //{"target_model_type", vector_la.at(1)},
//        {"target_model_type", "Fighter"},
//        {"target_max_Nx",vector_la.at(2)},
//        {"target_max_Ny",vector_la.at(3)},
//        {"target_min_Nx",vector_la.at(4)},
//        {"target_max_M",vector_la.at(5)},
//        {"target_practical_roof",vector_la.at(6)}
//    };
//    QJsonArray la_points;
//    //int count = 1;
//    for(int ii = 7; ii<vector_la.size(); ii+=4)
//    {
//        QJsonObject j_object_point
//        {
//            //{"point", count++},
//            {"x", vector_la.at(ii)},
//            {"y", vector_la.at(ii+1)},
//            {"z",vector_la.at(ii+2)},
//            {"vel",vector_la.at(ii+3)}
//        };
//        la_points.append(j_object_point);
//    }
//    j_object_la.insert("target_points", QJsonValue(la_points));
//    array_la_all.append(j_object_la);
//}

//j_object.insert("pbu",QJsonValue(j_oblect_pbu));
//j_object.insert("pu",QJsonValue(array_pu));
//j_object.insert("rls",QJsonValue(array_radar));
//j_object.insert("la", QJsonValue(array_la_all));

//fileJson.write(QJsonDocument(j_object).toJson());

//fileJson.close();
