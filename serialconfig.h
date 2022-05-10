/*
 *
 * @Author Riccardo Iacob
 * @File serialconfig.h
 * @Date 09/05/2022
 *
 * @Description this class holds the user-configurable properties of the QSerialPort class
 *
*/

#ifndef SERIALCONFIG_H
#define SERIALCONFIG_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialConfig
{
public:
    // setBaudRate
    QSerialPort::BaudRate baudRate = QSerialPort::Baud9600;
    // setDataBits
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    // setFlowControl
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
    // setParity
    QSerialPort::Parity parity = QSerialPort::NoParity;
    // setPortName
    QString portName;
    // setReadBufferSize
    qint64 readBufferSize = 0;
    // setStopBits
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    // Default configuration loader
    void defaultConfig();
    // Config valitator
    bool validateConfig();
};

#endif // SERIALCONFIG_H
