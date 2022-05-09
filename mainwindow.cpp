#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialconfigdialog.h"
#include "logger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a new serial port
    serialPort = new QSerialPort();
    // Create a logger
    logger = new Logger("MainWindow");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSerial_Configuration_triggered()
{
    SerialConfigDialog* dialog = new SerialConfigDialog(this);
    dialog->exec();

    serialConfig = dialog->getSerialConfig();

    // Make sure configuration exists
    if (serialConfig == NULL) {
        return;
    }

    // If the dialog return was accepted, connect to the selected port with the user defined configuration
    if (dialog->Accepted) {
        serialPort = new QSerialPort(serialConfig->portName);
        serialPort->setBaudRate(serialConfig->baudRate);
        serialPort->setDataBits(serialConfig->dataBits);
        serialPort->setFlowControl(serialConfig->flowControl);
        serialPort->setParity(serialConfig->parity);
        serialPort->setReadBufferSize(serialConfig->readBufferSize);
        serialPort->setStopBits(serialConfig->stopBits);
    }
}


void MainWindow::on_pushButtonConnectSerial_clicked()
{
    // If the serial config is null the user hasn't correcly configured serial yet
    if (serialConfig == NULL) {
        logger->log("Can't connect because serialConfig is invalid", Logger::CRITICAL);
        return;
    }

    // Open the serial port
    serialPort->open(QIODevice::ReadWrite);
    logger->log("Serial port open", Logger::INFO);
}


void MainWindow::on_pushButtonDisconnectSerial_clicked()
{
    // Close the serial port if it is open
    if (serialPort->isOpen()) {
        serialPort->close();
        logger->log("Serial port closed", Logger::INFO);
        return;
    }

    logger->log("Serial port already closed", Logger::WARN);
}

