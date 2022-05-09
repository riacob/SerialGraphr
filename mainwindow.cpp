#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialconfigdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSerial_Configuration_triggered()
{
    SerialConfigDialog* dialog = new SerialConfigDialog(this);
    dialog->exec();
}

