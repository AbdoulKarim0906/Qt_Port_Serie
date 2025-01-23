#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "arduino.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionEcho_triggered();
    void onEnvoi(QString text);

    void on_actionTimeSet_triggered();

    void on_actionTimeGet_triggered();

private:
    Ui::MainWindow *ui;
    Arduino arduino;
};
#endif // MAINWINDOW_H
