#include <QCloseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialconfigdialog.h"
#include "logger.h"
#include "QDebug"

void MainWindow::closeEvent(QCloseEvent *event)
{
    // On window close disconnect the serial port
    serialPort->disconnect();
    event->accept();
}

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

    // If the dialog was accepted and the serial config is valid, initialize the QSerialPort with the given configuration
    if (dialog->Accepted) {
        serialConfig = dialog->getSerialConfig();
        if (serialConfig == NULL) {
            return;
        }
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
    //qDebug() << serialConfig->baudRate << serialConfig->dataBits << serialConfig->flowControl << serialConfig->parity << serialConfig->readBufferSize << serialConfig->stopBits;
    // If the serial config is null the user hasn't correcly configured serial yet
    if (serialConfig == NULL || !serialConfig->validateConfig()) {
        logger->log("Serial configuration is invalid", Logger::CRITICAL, true);
        return;
    }

    // Open the serial port
    QString connectionData = QString("Connected to %1, %2 Baud").arg(serialConfig->portName).arg(serialConfig->baudRate);
    serialPort->open(QIODevice::ReadWrite);
    logger->log("Serial port is open", Logger::INFO, true);
    ui->labelConnectionStatus->setText(connectionData);
    qDebug() << "Connected to serial with settings" << serialConfig->portName << serialConfig->baudRate << serialConfig->dataBits << serialConfig->flowControl << serialConfig->parity << serialConfig->readBufferSize << serialConfig->stopBits;
}


void MainWindow::on_pushButtonDisconnectSerial_clicked()
{
    // Close the serial port if it is open
    if (serialPort->isOpen()) {
        serialPort->close();
        ui->labelConnectionStatus->setText("Disconnected");
        logger->log("Serial port is closed", Logger::INFO, true);
        return;
    }

    logger->log("Serial port is already closed", Logger::WARN, true);
    serialPort = new QSerialPort(serialConfig->portName);
}


void MainWindow::on_pushButtonSend_clicked()
{
    // If the serial port is open do nothing
    if (!serialPort->isOpen()) {
        logger->log("Serial port is closed", Logger::WARN, true);
        return;
    }


    serialPort->write(ui->plainTextEditSnd->toPlainText().toStdString().c_str());
    logger->log("Data transmitted to serial port", Logger::INFO, true);
}


void MainWindow::on_pushButton_clicked()
{
    QByteArray buf;
    QString str;
    buf = serialPort->readAll();
    str = tr(buf);
    ui->plainTextEditRec->clear();
    ui->plainTextEditRec->appendPlainText(str);
}

