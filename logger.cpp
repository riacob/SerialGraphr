#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

#include "logger.h"

void Logger::log(const char* logStr, messageType msgType, bool msgBox)
{
    QString dateTime;
    dateTime.append("[");
    dateTime.append(QDateTime::currentDateTime().toString());
    dateTime.append("]");

    QString messageTypeStr;
    QMessageBox::Icon messageBoxIcon;
    switch (msgType) {
    case INFO: messageTypeStr = "[INFO]"; messageBoxIcon = QMessageBox::Information; break;
    case WARN: messageTypeStr = "[WARN]"; messageBoxIcon = QMessageBox::Warning; break;
    case CRITICAL: messageTypeStr = "[CRITICAL]"; messageBoxIcon = QMessageBox::Critical;break;
    }

    QFile myFile(logFilePath);
    myFile.open(QIODevice::WriteOnly | QFile::Append);
    QTextStream myLog(&myFile);
    myLog << dateTime << "[" << parentClassName << "]" << messageTypeStr << " " << logStr << Qt::endl;


    if (msgBox && msgBoxEnabled) {
        QMessageBox messageBox;

        messageBox.setText(logStr);
        messageBox.setIcon(messageBoxIcon);

        messageBox.exec();
    }

}

Logger::Logger(const char* parentClassName)
{
    this->parentClassName = parentClassName;
}


