#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "serialconfig.h"
#include "logger.h"

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
    void on_actionSerial_Configuration_triggered();

    void on_pushButtonConnectSerial_clicked();

    void on_pushButtonDisconnectSerial_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButton_clicked();

private:
    void closeEvent(QCloseEvent *event);
    Logger* logger;
    SerialConfig* serialConfig = NULL;
    QSerialPort* serialPort;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
