#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

#include "logger.h"

void Logger::log(const char* logStr, messageType msgType)
{
    QString dateTime;
    dateTime.append("[");
    dateTime.append(QDateTime::currentDateTime().toString());
    dateTime.append("]");

    QString messageTypeStr;
    switch (msgType) {
    case INFO: messageTypeStr = "[INFO]"; break;
    case WARN: messageTypeStr = "[WARN]"; break;
    case CRITICAL: messageTypeStr = "[CRITICAL]"; break;
    }

    QFile myFile(logFilePath);
    myFile.open(QIODevice::WriteOnly | QFile::Append);
    QTextStream myLog(&myFile);
    myLog << dateTime << " " << messageTypeStr << " " << logStr << Qt::endl;
}
