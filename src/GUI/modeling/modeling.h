#ifndef MODELING_H
#define MODELING_H

#include <QWidget>
#include <QInputDialog>
#include <QThread>
#include <QLayout>
#include "qcustomplot.h"
#include "aircraft_model.h"
#include "aircraft_pbu.h"
#include "launcher_model.h"
#include "pbu_model.h"
#include "radar_model.h"
#include "zur_model.h"

#define _STEP_TIME_ 1


namespace Ui {
class modeling;
}

class modeling : public QWidget
{
    Q_OBJECT

public:
    explicit modeling(QWidget *parent = 0);
    ~modeling();

public slots:

    void accept_json(QString);

private slots:

    void change_step(int index);

private:
    Ui::modeling *ui;

    QString name_config;

    QMap <int, radar_model> map_radars;

    QMap <int, launcher_model> map_launchers;

    QMap <int, zur_model> map_zurs;

    QMap <int, aircraft_model> map_aircraft_m;

    QMap <int, aircraft_pbu*> map_aircraft_pbu;

    ///
    /// \brief Вектора, содержащие координаты всех ПУ на полотне
    ///
    QVector<double> vector_x_pu, vector_y_pu, vector_z_pu, vector_range_pu;
    ///
    /// \brief Вектора, содержащие координаты всех РЛС на полотне
    ///
    QVector<double> vector_x_radar, vector_y_radar, vector_z_radar, vector_range_radar;
    ///
    /// \brief Вектора, содержащие координаты ПБУ на полотне
    ///
    QVector<double> x_pbu, y_pbu, z_pbu, range_pbu;

    //QHash <int, aircraft_model> map_aircraft_m;

    pbu_model pbu;

    int count_graph = 3;

    double end_time;

    enum num_stationary_plots
    {
        pbu_plot, ///< график ПБУ
        radar_plot,///< график РЛС
        launcher_plot,///< график ПУ
    };

    enum num_read_method
    {
        pbu_read, ///<
        aircraft_read,///<
        launcher_read,///<
        rls_read,///<
        zur_read,///<
    };

    void clear_data();

    void set_data(QString _name_config);

    void set_data_plot();

    void create_stationary_graphs();

    void set_stationary_elements();

    void create_moving_graphs();

    void plot_1(int number,
                QVector<double> vector_z,
                QVector<double> vector_range);
    void plot_2(int number,
                QVector<double> vector_x,
                QVector<double> vector_y);

    void set_pen(int index);

    void set_pen_radius(int number);

    void read_csv();

    void pick_read_method(int state, QString _name_csv);

    void read_aircraft_csv(QString name_csv);

    void read_zur_csv(QString name_csv);

    void read_radar_csv(QString name_csv);

    void read_pbu_csv(QString name_csv);

    void read_launcher_csv(QString name_csv);

    void create_dynamic_elements();

    void append_layout_pu();

};

#endif // MODELING_H
