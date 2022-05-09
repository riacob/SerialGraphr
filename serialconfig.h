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
    // setBreakEnabled
    bool breakEnabled = true;
    // setDataBits
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    // setDataTerminalReady
    bool setDataTerminalReady = false;
    // setFlowControl
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
    // setParity
    QSerialPort::Parity parity = QSerialPort::NoParity;
    // setPortName
    QString portName;
    // setReadBufferSize
    qint64 readBufferSize = 0;
    // setRequestToSend
    bool requestToSend = false;
    // setStopBits
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
};

#endif // SERIALCONFIG_H
