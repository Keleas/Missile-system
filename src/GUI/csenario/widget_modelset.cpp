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

    ui->customPlot->setInteractions(/*QCP::iRangeDrag |*/ QCP::iRangeZoom);

//    QIcon icon(":/src/images/pu.png");

    ui->customPlot->xAxis->setRange(-100000, 100000);
    ui->customPlot->yAxis->setRange(-100000, 100000);

    ui->customPlot->xAxis->setLabel("x, м");
    ui->customPlot->yAxis->setLabel("y, м");

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

    connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)),
            this, SLOT(get_pos_mouse_on_canvas(QMouseEvent*)));

    ccp_pbu.set_coordinates(0,0,0);
    ccp_pbu.set_id(0);
    x_pbu.append(0);
    y_pbu.append(0);
    plot(state_pbu, x_pbu, y_pbu);


    top_item_pbu = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_pbu);
    top_item_pbu->setText(0,"ПБУ");
    top_item_pbu->addChildren(ccp_pbu.get_item());

    top_item_radar = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_radar);
    top_item_radar->setText(0,"РЛС");

    top_item_pu = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_pu);
    top_item_pu->setText(0,"ПУ");

    top_item_aircraft = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(top_item_aircraft);
    top_item_aircraft->setText(0,"ЛА");

    ui->pushButton_modelling->setDisabled(true);

    //set_properties_antiaircraft();
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
    vector_item_zur.clear();

//    vector_data_aircraft.clear();
//    vector_data_pbu.clear();
//    vector_data_pu.clear();
//    vector_data_radar.clear();
//    vector_data_aircraft_all.clear();

    vector_aircrafts.clear();
    vector_launchers.clear();
    vector_radars.clear();

//    x_pbu.clear();
//    y_pbu.clear();

//    ccp_pbu.clearData();

    ui->lineEdit->clear();

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

void widget_modelset::get_pos_mouse_on_canvas(QMouseEvent *event)
{
    QString cord;
    double x = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = ui->customPlot->yAxis->pixelToCoord(event->pos().y());
    cord = "x = "+QString::number(x)+", y = "+QString::number(y);
    ui->lineEdit->setText(cord);
}

void widget_modelset::click_on_canvas(QMouseEvent *event)
{

    double x = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = ui->customPlot->yAxis->pixelToCoord(event->pos().y());

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
            add_point_items_aircraft(x, y,item);
            vector_item_aircraft.append(item);
            item_aircraft_added = true;
        }
        else
        {
            add_point_items_aircraft(x, y, vector_item_aircraft.last());
        }
    }break;
    case state_pbu:
    {
        add_point(x,y);
        plot(state_pbu, x_pbu, y_pbu);
//        vector_data_pbu.clear();
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
//             vector_data_pbu.append(list.at(ii).split(": ").at(1));
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
        set_pen_graph(index_aircraft);

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
//        vector_data_aircraft_all.append(vector_data_aircraft);
//        vector_data_aircraft.clear();
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
    plot(state_pbu, x_pbu, y_pbu);
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
    top_item_pbu->addChildren(ccp_pbu.get_item());

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

void widget_modelset::set_properties_antiaircraft(Antiaircraft *antiaircraft)
{
    QSqlQuery query(db);
    QString select = "SELECT nx_max, ny_max, nx_min, m_max, "
                     "practical_roof FROM aircrafts WHERE type = 'ЗУР'";
    query.exec(select);
    while (query.next())
    {
        antiaircraft->set_properties(query.value(0).toDouble(),
                              query.value(1).toDouble(),
                              query.value(2).toDouble(),
                              query.value(3).toDouble(),
                              query.value(4).toDouble());
    }
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
    craft->set_graph(index_aircraft);

    list<<"ID: "+QString::number(count_id)/*QString::number(_count)*/
       <<"Модель: "+buff
      <<"Имя модели: plane_"+ QString::number(vector_aircrafts.size());

    while (query.next())
    {
        craft->set_properties(query.value(0).toDouble(),
                              query.value(1).toDouble(),
                              query.value(2).toDouble(),
                              query.value(3).toDouble(),
                              query.value(4).toDouble());
    }

    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         _item->addChild(item_child);
         item_child->setText(0,list.at(ii));
//         vector_data_aircraft.append(list.at(ii).split(": ").at(1));
    }
    vector_aircrafts.append(craft);
}

void widget_modelset::add_children_items_pu(double x, double y)
{
    ++count_id;
    int count = vector_item_pu.size();

    Launcher* pu = new Launcher();
    pu->set_name("ПУ_"+QString::number(count));
    pu->set_id(count_id);
    pu->set_coordinates(x,y,0);
    vector_launchers.append(pu);

    QTreeWidgetItem* item = new QTreeWidgetItem();
    QList<QString> list;
    list<<"ID: "+QString::number(count_id)
        <<"x: "+QString::number(x)
        <<"y: "+QString::number(y)
        <<"z: 0";
    list.append(input_dialog_pu());
    vector_item_pu.append(item);
    top_item_pu->addChild(item);
    item->setText(0, "ПУ_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
//         vector_data_pu.append(list.at(ii).split(": ").at(1));
    }
    QTreeWidgetItem* item_child = new QTreeWidgetItem();
    item->addChild(item_child);
    item_child->setText(0,"ЗУР");

    QVector<int> id_zur;
    for (int ii=count_id+1;
         ii<count_id+vector_launchers.last()->count_zur()+1;
         ++ii )
        id_zur.append(ii);
    count_id+=vector_launchers.last()->count_zur();

    QVector<Antiaircraft*> zurs;

    ///@note переделать добавление в дерево
    for (int ii = 0; ii<id_zur.size();++ii)
    {
        QTreeWidgetItem* item_roket = new QTreeWidgetItem();        
        item_child->addChild(item_roket);
        item_roket->setText(0,"ЗУР_"+QString::number(vector_item_zur.size())+": "
                            +QString::number(id_zur.at(ii)));
        Antiaircraft *zur = new Antiaircraft();
        zur->set_id(id_zur.at(ii));
        zur->set_name("zur_"+QString::number(vector_item_zur.size()));
        vector_item_zur.append(item_roket);
        pu->append_zur(zur);
    }
    set_radius_launcher(pu);
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
    rls->set_model(str);
    rls->set_name("РЛС_"+QString::number(count));
    vector_radars.append(rls);

    QList<QString> list;
    list<<"ID: "+QString::number(count_id)
        <<"Модель: "
        <<"x: "+QString::number(x)
        <<"y: "+QString::number(y)
        <<"z: 0";
    list[1]+=str;

    list.append(input_propertes_radar(str,rls));

    vector_item_radar.append(item);
    top_item_radar->addChild(item);
    item->setText(0, "РЛС_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
//         vector_data_radar.append(list.at(ii).split(": ").at(1));
    }
    set_radius_radar(rls);
    //qDebug()<<vector_data_radar;
}

void widget_modelset::add_point_items_aircraft(double x, double y,
                                            QTreeWidgetItem* _item)
{
    QVector<QString> vector = input_dialog_point_aircraft();

    Point *point = new Point();
    point->set_coordinates(x,y,vector.at(0).toDouble());
    point->set_velocity(vector.at(1).toDouble());

    vector_aircrafts.last()->append_point(point);

    QList<QString> list;
    list<<"#"+QString::number(vector_x_aircraft.size())
        <<"x[м]: "+QString::number(x)
        <<"y[м]: "+QString::number(y)
        <<"z[м]: "+vector.at(0)
        <<"Скорость[км/ч]: "+vector.at(1);
    QTreeWidgetItem* item_child = new QTreeWidgetItem();
    _item->addChild(item_child);
    item_child->setText(0,list.at(0));    
    for (int ii=1;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_grandchild = new QTreeWidgetItem();
         item_child->addChild(item_grandchild);
         item_grandchild->setText(0,list.at(ii));
//         vector_data_aircraft.append(list.at(ii).split(": ").at(1));
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
    QLabel* label_z = new QLabel("z[м]");
    QLabel* label_velocity = new QLabel("Скорость[км/ч]");
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
                       QString::number(vector_aircrafts.size()));
    }
    if (_state==state_radar)
    {
        QString select = "SELECT type FROM radars";
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

QList<QString> widget_modelset::input_propertes_radar(QString model, Radar* rls)
{
    QList<QString> results;

    QSqlQuery query(db);
    QString select = "SELECT type,Dmax,Dmin FROM radars WHERE type = '"
                                                            +model+"'";
    if(!query.exec(select))
    {
        qDebug()<<query.lastError()<<"select radar_D";
    }
    while (query.next())
    {
        results<<"Dmax: "+query.value(1).toString()
         <<"Dmin: "+query.value(2).toString();
    }
    rls->set_is_pisets_kolya(model, db);

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
    QLabel* label_radius = new QLabel("Радиус действия (м):");
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

    lineEdit_radius->setText("100000");
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
        results.append("Радиус действия (м): "+lineEdit_radius->text());
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
        name=lineEdit_name->text() + ".json";
        name_std_config = name.toStdString().c_str();
        name_config = lineEdit_name->text() + ".json";
        serialization_json(name);
        ui->label_name_config->setText(name);

        msgBox.setText("Данные сохранены в файл: "+name);
        msgBox.exec();
    }
    ui->label_name_config->setText(name);
    ui->pushButton_modelling->setDisabled(false);
}

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
        Launcher* pu = launcher_count;
        for(Antiaircraft* launcher_zur : pu->get_zurs())
        {
            objArray.append(launcher_zur->toJsonObject(db));
        }
    }
    //objArray.append(anticraft.toJsonObject());

    rootJsonObj.insert("objects",QJsonValue(objArray));

    fileJson.write(QJsonDocument(rootJsonObj).toJson());
    fileJson.close();
}

void widget_modelset::deserialization_json(QString _config_name)
{
    QFile fileJson(_config_name);
    fileJson.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(fileJson.readAll());
    QJsonObject j_object = doc.object();

    QString name = j_object["scenario_name"].toString();
    ui->time_modelinglineEdit->setText(j_object["end_time"].toString());

    name_config = _config_name;
    name_std_config = _config_name.toStdString();
    ui->label_name_config->setText(name);

    //set_properties_antiaircraft();

    QJsonArray array = j_object["objects"].toArray();
    for (QJsonValue value : array)
    {
//        if (value.toObject()["model_name"].toString() == "PBU")
//        {
//            ccp_pbu.set_id(value.toObject()["id"].toInt());
//            ccp_pbu.set_coordinates(
//                        value.toObject()["initial_data"].toObject()["x"].toDouble(),
//                    value.toObject()["initial_data"].toObject()["y"].toDouble(),
//                    value.toObject()["initial_data"].toObject()["z"].toDouble());
//        }
        if (value.toObject()["model_name"].toString() == "RLS")
        {
            QJsonObject j_object_radar = value.toObject()["initial_data"].toObject();
            Radar* radar = new Radar(j_object_radar);
            radar->set_id(value.toObject()["id"].toInt());
            radar->set_model(value.toObject()["model"].toString());
            vector_radars.append(radar);
        }

        if (value.toObject()["model_name"].toString() == "PU")
        {
            QJsonObject j_object_launcher = value.toObject()["initial_data"].toObject();
            Launcher* pu = new Launcher(j_object_launcher,db);
            pu->set_id(value.toObject()["id"].toInt());
            vector_launchers.append(pu);
        }

        if (value.toObject()["model_name"].toString() == "AirTarget")
        {
            QJsonObject j_object_craft = value.toObject()["initial_data"].toObject();
            Aircraft *craft = new Aircraft(j_object_craft);
            craft->set_id(value.toObject()["id"].toInt());
            vector_aircrafts.append(craft);
        }
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
    set_elements_modelset();
    ui->pushButton_modelling->setDisabled(false);
}


void widget_modelset::set_elements_modelset()
{
    set_tree_items();
    set_stationary_graphs();
    set_aircraft_graphs();
    set_radius_graphs();
}

void widget_modelset::set_tree_items()
{
    int count;
    //top_item_pbu->addChildren(ccp_pbu.get_item());
    for (Radar *rls : vector_radars)
    {
        if(count_id<rls->get_id())
        {
            count_id = rls->get_id();
        }
        count = vector_item_radar.size();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item = rls->get_item(count);
        vector_item_radar.append(item);
        top_item_radar->addChild(item);
    }
    for (Launcher *pu : vector_launchers)
    {
        if(count_id<pu->get_zurs().last()->get_id())
        {
            count_id = pu->get_zurs().last()->get_id();
        }
        count = vector_item_pu.size();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item = pu->get_item(count);
        vector_item_pu.append(item);
        top_item_pu->addChild(item);
        QTreeWidgetItem* item_child = new QTreeWidgetItem();
        item_child->setText(0,"ЗУР");
        for (int ii=0; ii<pu->get_zurs().size();++ii)
        {
            QTreeWidgetItem* item_roket = new QTreeWidgetItem();
            item_roket = pu->get_zurs().at(ii)->get_item(vector_item_zur.size());
            item_child->addChild(item_roket);
            vector_item_zur.append(item_roket);
        }
        item->addChild(item_child);
    }
    for (Aircraft *craft : vector_aircrafts)
    {
        if(count_id<craft->get_id())
        {
            count_id = craft->get_id();
        }
        count = vector_item_aircraft.size();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item = craft->get_item(count);
        vector_item_aircraft.append(item);
        top_item_aircraft->addChild(item);
        for (int ii=0;ii<craft->get_points().size() ; ++ii)
        {
            item->addChild(craft->get_points().at(ii)->get_item(ii));
        }
    }
}

void widget_modelset::set_stationary_graphs()
{
    for (Radar* rls : vector_radars)
    {
        vector_x_radar.append(rls->get_x());
        vector_y_radar.append(rls->get_y());
    }
    plot(state_radar,vector_x_radar,vector_y_radar);
    for (Launcher* pu : vector_launchers)
    {
        vector_x_pu.append(pu->get_x());
        vector_y_pu.append(pu->get_y());
    }
    plot(state_pu,vector_x_pu,vector_y_pu);
}

void widget_modelset::set_aircraft_graphs()
{
    index_aircraft = (ui->customPlot->graphCount())-1;
    for (Aircraft* craft : vector_aircrafts)
    {
        ui->customPlot->addGraph();
        index_aircraft = (ui->customPlot->graphCount())-1;
        craft->set_graph(index_aircraft);
        plot(index_aircraft,craft->get_vector_x(), craft->get_vector_y());
        set_pen_graph(index_aircraft);
    }
    ui->customPlot->replot();
}

void widget_modelset::set_radius_graphs()
{
    index_aircraft = (ui->customPlot->graphCount())-1;
    for (Radar* rls : vector_radars)
    {
        ui->customPlot->addGraph();
        index_aircraft = (ui->customPlot->graphCount())-1;
        rls->set_graph(index_aircraft);
        plot(index_aircraft,rls->get_rad_max_x(), rls->get_rad_max_y());
        set_pen_radius(index_aircraft);
    }
    for (Launcher* pu : vector_launchers)
    {
        ui->customPlot->addGraph();
        index_aircraft = (ui->customPlot->graphCount())-1;
        pu->set_graph(index_aircraft);
        plot(index_aircraft,pu->get_rad_x(), pu->get_rad_y());
        set_pen_radius(index_aircraft);
    }
    ui->customPlot->replot();
}

void widget_modelset::set_radius_radar(Radar* rls)
{
    //qDebug
    ui->customPlot->addGraph();
    index_aircraft = (ui->customPlot->graphCount())-1;
    rls->set_graph(index_aircraft);
    plot(index_aircraft,rls->get_rad_max_x(), rls->get_rad_max_y());
    set_pen_radius(index_aircraft);
    ui->customPlot->replot();
}

void widget_modelset::set_radius_launcher(Launcher* pu)
{
    //qDebug
    ui->customPlot->addGraph();
    index_aircraft = (ui->customPlot->graphCount())-1;
    pu->set_graph(index_aircraft);
    plot(index_aircraft,pu->get_rad_x(), pu->get_rad_y());
    set_pen_radius(index_aircraft);
    ui->customPlot->replot();
}

void widget_modelset::on_pushButton_modelling_clicked()
{
    emit start_modelling(0);
    emit set_json(name_config);
}

void widget_modelset::set_pen_graph(int number)
{
    QPen pen_line(Qt::red, 3, Qt::DashDotLine,
             Qt::RoundCap, Qt::RoundJoin);
    QColor color( qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0, 255 );
    pen_line.setColor(color);
    ui->customPlot->graph(number)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(number)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(number)->setPen(pen_line);
}

void widget_modelset::set_pen_radius(int number)
{
    QPen pen_line(Qt::red, 3, Qt::DashDotLine,
             Qt::RoundCap, Qt::RoundJoin);
    QColor color( qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0, 255 );
    pen_line.setColor(color);
    ui->customPlot->graph(number)->
            setScatterStyle(QCPScatterStyle::ssDot);
    ui->customPlot->graph(number)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(number)->setPen(pen_line);
}
