#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QMessageLogger>

#include "serialconfigdialog.h"
#include "ui_serialconfigdialog.h"
#include "logger.h"

SerialConfigDialog::SerialConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialConfigDialog)
{
    ui->setupUi(this);

    // Create a new serial configuration
    serialConfig = new SerialConfig();

    // Create a new logger
    logger = new Logger("SerialConfigDialog");

    // Refresh the connected devices
    refreshDevices();
}

SerialConfigDialog::~SerialConfigDialog()
{
    delete ui;
}

void SerialConfigDialog::refreshDevices()
{
    // Clear the devices listWidget
    ui->listWidgetSerialDevices->clear();
    // Get the device list
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    // Iterate trough every device in the list and add it to the devices listWidget
    // Label is composed of portName and description
    // For example, "COM0 - Arduino Uno"
    for (int i = 0; i < serialPorts.length(); i++) {
        QString serialDeviceLabel;
        serialDeviceLabel.append(serialPorts.at(i).portName());
        serialDeviceLabel.append(" - ");
        serialDeviceLabel.append(serialPorts.at(i).description());
        ui->listWidgetSerialDevices->addItem(serialDeviceLabel);
    }
}

void SerialConfigDialog::on_pushButtonRefreshDevices_clicked()
{
    refreshDevices();
}

void SerialConfigDialog::saveConfig()
{
    // Save the user defined serial port config
    // Eventual invalid config data will be handled later by validateConfig()

    // baudRate
    switch (ui->comboBoxBaudRate->currentIndex()) {
        case 0: serialConfig->baudRate = QSerialPort::Baud1200; break;
        case 1: serialConfig->baudRate = QSerialPort::Baud2400; break;
        case 2: serialConfig->baudRate = QSerialPort::Baud4800; break;
        case 3: serialConfig->baudRate = QSerialPort::Baud9600; break;
        case 4: serialConfig->baudRate = QSerialPort::Baud19200; break;
        case 5: serialConfig->baudRate = QSerialPort::Baud38400; break;
        case 6: serialConfig->baudRate = QSerialPort::Baud57600; break;
        case 7: serialConfig->baudRate = QSerialPort::Baud115200; break;
    }

    // dataBits
    switch (ui->comboBoxDataBits->currentIndex()) {
        case 0: serialConfig->dataBits = QSerialPort::Data5; break;
        case 1: serialConfig->dataBits = QSerialPort::Data6; break;
        case 2: serialConfig->dataBits = QSerialPort::Data7; break;
        case 3: serialConfig->dataBits = QSerialPort::Data8; break;
    }

    // flowControl
    switch (ui->comboBoxFlowControl->currentIndex()) {
        case 0: serialConfig->flowControl = QSerialPort::NoFlowControl; break;
        case 1: serialConfig->flowControl = QSerialPort::HardwareControl; break;
        case 2: serialConfig->flowControl = QSerialPort::SoftwareControl; break;
    }

    // parity
    switch (ui->comboBoxParity->currentIndex()) {
        case 0: serialConfig->parity = QSerialPort::NoParity; break;
        case 1: serialConfig->parity = QSerialPort::EvenParity; break;
        case 2: serialConfig->parity = QSerialPort::OddParity; break;
        case 3: serialConfig->parity = QSerialPort::SpaceParity; break;
        case 4: serialConfig->parity = QSerialPort::MarkParity; break;
    }

    // portName
    // Make sure an element is selected
    if (ui->listWidgetSerialDevices->selectedItems().length() > 0) {
        // Get the serial port name from the first 4 characters of the element in the listWidget
        // For example, "COM0"
        serialConfig->portName = ui->listWidgetSerialDevices->selectedItems().at(0)->text().mid(0, 4);
    }

    // readBufferSize
    serialConfig->readBufferSize = ui->spinBoxBufferSize->value();

    // stopBits
    switch (ui->comboBoxStopBits->currentIndex()) {
        case 0: serialConfig->stopBits = QSerialPort::OneStop; break;
        case 1: serialConfig->stopBits = QSerialPort::OneAndHalfStop; break;
        case 2: serialConfig->stopBits = QSerialPort::TwoStop; break;
    }

}

SerialConfig* SerialConfigDialog::getSerialConfig()
{
    // Return the serial configuration
    // Note that this will be a null pointer if the configuration is invalid
    return serialConfig;
}


void SerialConfigDialog::on_pushButtonExitOk_clicked()
{
    // If the exit ok button is pressed
    // We return reject if configuration is invalid, accept if it is valid
    // First, we need to save the user-inputted settings into the config class
    saveConfig();
    // Then we validate the aforementioned config, if it is invalid
    if (!serialConfig->validateConfig()) {
        // Clear the serial configuration
        serialConfig->defaultConfig();
        // Exit from the dialog window
        this->reject();
        logger->log("Serial configuration is invalid", Logger::CRITICAL, true);
        return;
    }

    // Return accept because config is valid
    this->accept();
    logger->log("Serial configuration saved", Logger::INFO, true);
    return;
}


void SerialConfigDialog::on_pushButtonExitCancel_clicked()
{
    // If the exit cancel button is pressed we return reject
    this->reject();
    logger->log("Serial configuration not saved", Logger::INFO, true);
    return;
}

