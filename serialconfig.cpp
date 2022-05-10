#include "serialconfig.h"

void SerialConfig::defaultConfig()
{
    // setBaudRate
    baudRate = QSerialPort::Baud9600;
    // setDataBits
    dataBits = QSerialPort::Data8;
    // setFlowControl
    flowControl = QSerialPort::NoFlowControl;
    // setParity
    parity = QSerialPort::NoParity;
    // setPortName
    portName = "NOTAPORT";
    // setReadBufferSize
    readBufferSize = 0;
    // setStopBits
    stopBits = QSerialPort::OneStop;
}

bool SerialConfig::validateConfig()
{
    // Return code, true if config is valid, false if it is invalid
    bool retCode = true;

    // Port name regex for windows, mac & linux
    if (!(portName.startsWith("COM") || portName.startsWith("tty"))) {
        retCode = false;
        //logger->log("PortName is NULL", Logger::CRITICAL, true);
    }

    // readBufferSize must be >= 0
    if (readBufferSize < 0) {
        retCode = false;
        //logger->log("ReadBufferSize is < 0", Logger::CRITICAL, true);
    }

    return retCode;
}
