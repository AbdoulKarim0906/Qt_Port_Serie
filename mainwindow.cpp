#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbxPortName->addItems(arduino.portList);
    for(int i=0; i <arduino.portList.size(); i++)
        if(arduino.portList[i].contains("Arduino"))
            ui->cbxPortName->setCurrentIndex(i);
    connect(&arduino,SIGNAL(envoi(QString)), SLOT(onEnvoi(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    int baudRate = ui->cbxBaud->currentText().toInt();
    if(arduino.open(ui->cbxPortName->currentIndex(), baudRate))
        ui->textEdit->append("Port " +ui->cbxPortName->currentText() +" ouvert ");

}

void MainWindow::on_actionEcho_triggered()
{
    if(arduino.echo())
        ui->textEdit->append("Envoi ECHO");

}

void MainWindow::onEnvoi(QString text)
{
    ui->textEdit->append(text);
    statusBar()->showMessage("Message reçu",3000);
}

void MainWindow::on_actionTimeSet_triggered()
{
    if(arduino.setTime())
        ui->textEdit->append("Mis à l'heure");
}

void MainWindow::on_actionTimeGet_triggered()
{
    if(arduino.getTime())
        ui->textEdit->append("Renvoi de l'heure");

}
