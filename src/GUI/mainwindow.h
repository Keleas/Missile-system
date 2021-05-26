#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>

#if QT_VERSION < 0x050000
    #include <QtConcurrentRun>
#else
    #include <QtConcurrent/QtConcurrentRun>
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void need_progess_bar();

private:
    Ui::MainWindow *ui;

    QVector<QFutureWatcher<void> *> v_futureWatcher;
    QVector<QProgressDialog *> v_progress;
    QVector<QFutureInterface<void> *> v_futureInterface;

};
#endif // MAINWINDOW_H
