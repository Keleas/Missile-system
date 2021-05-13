#ifndef WIDGET_MODELSET_H
#define WIDGET_MODELSET_H

#include <QWidget>
#include "qcustomplot.h"
#include <QtSql>

namespace Ui {
class widget_modelset;
}

class widget_modelset : public QWidget
{
    Q_OBJECT

public:
    explicit widget_modelset(QWidget *parent = 0);
    ~widget_modelset();
    ///
    /// \brief Функция очищает переменные класса, элементы дерева
    ///
    void clearData();

    ///
    /// \brief Функция возвращает имя конфиг. файла
    /// \return имя файла
    ///
    std::string get_name_config() const{return name_config;}

    QSqlDatabase get_db() const{return  db;};

private:
    Ui::widget_modelset *ui;
    /// \brief объект подключения к бд
    QSqlDatabase db;
    ///
    /// \brief Вектора, содержащие координаты всех ПУ на полотне
    ///
    QVector<double> vector_x_pu, vector_y_pu;
    ///
    /// \brief Вектора, содержащие координаты одного ЛА на полотне
    ///
    QVector<double> vector_x_la, vector_y_la;
    ///
    /// \brief Вектора, содержащие координаты всех РЛС на полотне
    ///
    QVector<double> vector_x_radar, vector_y_radar;
    ///
    /// \brief Вектора, содержащие координаты ПБУ на полотне
    ///
    QVector<double> x_pbu, y_pbu;

    QPen pen_line;
    ///
    /// \brief Текущее состояние вкладки
    ///
    enum State_buttons
    {
        state_pbu, ///< зажата кнопка ПБУ
        state_radar,///< зажата кнопка РЛС
        state_pu,///< зажата кнопка ПУ
        state_la///< зажата кнопка ЛА
    };
    ///
    /// \brief Текущий индекс графика для рисования ЛА
    ///
    int index_la;
    ///
    /// \brief Текущее состояние вкладки
    ///
    int state_buttons;
    ///
    /// \brief
    ///
    int count_id = 0;
    /// \brief Указатель на самый верхний элемент дерева для объектов
    QTreeWidgetItem* top_item_pbu, *top_item_pu, *top_item_la, *top_item_radar;
    /// \brief Указатель дочерний элемент top_item_pbu
    QTreeWidgetItem* item_pbu /*item_maneuver*/;
    /// \brief Вектор указателей дочерних элементов объектов
    QVector<QTreeWidgetItem*> vector_item_pu, vector_item_radar, vector_item_la;
    /// \brief Вектор, содержащий информацию о ПУ
    QVector<QString> vector_data_pu,
    /// \brief Вектора, содержащий информацию о РЛС
    vector_data_radar,
    /// \brief Вектора, содержащий информацию о ПБУ
    vector_data_pbu,
    /// \brief Вектора, содержащий информацию о единичном ЛА
    vector_data_la;
    /// \brief Вектор, содержащий вектора с данными о всех ЛА
    QVector<QVector<QString>> vector_data_la_all;
    /// \brief Флаг поставленной начальной точки траектории ЛА
    bool item_la_added = false;
    /// \brief Имя конфиг. файла
    std::string name_config;
    ///
    /// \brief Функция, добавляющая координаты в вектора объекта
    /// \param[in] x - координата Х
    /// \param[in] y - координата Y
    ///
    void add_point(double x, double y);
    ///
    /// \brief Функция, добавляющая график на полотно
    /// \param[in] number - индекс графика
    /// \param[in] vector_x - координаты X объекта
    /// \param[in] vector_y - координаты Y объекта
    ///
    void plot(int number,
              QVector<double> vector_x,
              QVector<double> vector_y);
    ///
    /// \brief Функция, ставящая вкладку в состояние State_buttons
    /// \param[in] state - параметр состояния
    ///
    void set_state_buttons(int state);
    ///
    /// \brief Функция, резервирующая первые три индекса графиков
    ///  для последующего отображения объектов, которые не имеют траекторий
    ///
    void create_stationary_elements();

//    int get_state_buttons();

    ///
    /// \brief Функция, удаляющая элементы в дереве
    /// \param[in] QTreeWidgetItem* - указатель на главный элемент дерева
    ///
    void remove_tree_items(QTreeWidgetItem*);
    ///
    /// \brief Функция, добавляющая дочерний элемент ПУ в дерево с информацией
    /// и заполняющая vector_data_pu
    /// \param[in] x - координата Х
    /// \param[in] y - координата Y
    ///
    void add_children_items_pu(double x, double y);
    ///
    /// \brief Функция, добавляющая дочерний элемент РЛС в дерево с информацией
    /// и заполняющая vector_data_radar
    /// \param[in] x - координата Х
    /// \param[in] y - координата Y
    ///
    void add_children_items_radar(double x, double y);
    ///
    /// \brief Функция, добавляющая дочерний элемент ЛА в дерево с информацией
    /// без траекторий и заполняющая vector_data_la
    /// \param[in] QTreeWidgetItem* - указатель на элемент ЛА в дереве
    /// \param[in] _count - ID ЛА
    ///
    void add_basic_items_la(QTreeWidgetItem* _item, int _count);
    ///
    /// \brief Функция, добавляющая дочерний элемент ЛА в дерево с информацией
    /// о точке траектории и заполняющая vector_data_la
    /// \param[in] x - координата Х
    /// \param[in] y - координата Y
    /// \param[in] QTreeWidgetItem* - указатель на элемент ЛА в дереве
    ///
    void add_children_items_la(double x, double y, QTreeWidgetItem *_item);
    ///
    /// \brief Функция, вызывающая диалог для заполнения информации точки
    ///  траектории
    /// \return вектор с информацией о точке траектории
    ///
    QVector<QString> input_dialog_point_la();
    ///
    /// \brief Функция, вызывающая диалог для заполнения доп. информации ПУ
    /// \return лист с доп. информацией о ПУ
    ///
    QList<QString> input_dialog_pu();
    ///
    /// \brief Функция, вызывающая диалог для заполнения доп. информации РЛС
    /// \return лист с доп. информацией о РЛС
    ///
    QList<QString> input_dialog_radar();
    ///
    /// \brief Функция, вызывающая диалог для выбора модели объекта
    /// \param[in] _state - тип объекта
    /// \return строка с номером модели
    ///
    QString input_dialog_model(int _state);
    ///
    /// \brief Функция, заполняющая csv файл данными об объектах кроме ЛА
    /// \param[in] type_object - тип объекта
    /// \param[in] num_objects - количество объектов
    /// \param[in] num_params - количество параметров
    /// \param[in] params - вектор, содержащий все информацию об объекте
    /// \param[in] config_name - имя конфиг. файла
    ///
    void fill_csv(QString type_object,
                     int num_objects,
                     int num_params,
                     QVector <QString> params,
                     QString config_name);
    ///
    /// \brief Функция, заполняющая csv файл данными о ЛА
    /// \param[in] type_object - тип объекта
    /// \param[in] num_objects - количество объектов
    /// \param[in] config_name - имя конфиг. файла
    ///
    void fill_csv_for_la(QString type_object,
                            int num_objects,
                            QString config_name);

    ///
    /// \brief Функция, заполняющая json файл данными c GUI
    /// \param[in] _config_name - имя конфиг. файла
    ///
    void serialization_json(QString _config_name);

    ///
    /// \brief Функция, читающая json файл
    /// \param[in] _config_name - имя конфиг. файла
    ///
    void deserialization_json(QString _config_name);

private slots:
    ///
    /// \brief Слот, обработки нажатия клавиши мыши на полотно
    /// \param[in] event - указатель на событие мыши
    ///
    void click_on_canvas(QMouseEvent *event);
    ///
    /// \brief Слот, обработки нажатия кнопки "РЛС"
    /// \param[in] state - состояние клавиши
    ///
    void button_radar_toggled(bool state);
    ///
    /// \brief Слот, обработки нажатия кнопки "ЛА"
    /// \param[in] state - состояние клавиши
    ///
    void button_la_toggled(bool state);
    ///
    /// \brief Слот, обработки нажатия кнопки "ПУ"
    /// \param[in] state - состояние клавиши
    ///
    void button_pu_toggled(bool state);
    ///
    /// \brief Слот, обработки нажатия кнопки "ПБУ"
    /// \param[in] state - состояние клавиши
    ///
    void button_pbu_toggled(bool state);
    ///
    /// \brief Слот, обработки нажатия кнопки "Очистить"
    ///
    void on_pushButton_clear_clicked();

    //void add_maneuver(QMouseEvent* _event);
    ///
    /// \brief Слот, обработки нажатия кнопки "Сохранить"
    ///
    void on_save_pushButton_clicked();
    void on_pushButton_open_clicked();
};

#endif // WIDGET_MODELSET_H
