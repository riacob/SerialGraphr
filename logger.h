/*
 *
 * @Author Riccardo Iacob
 * @File serialconfig.h
 * @Date 09/05/2022
 *
 * @Description this class is used to log the given string to a file with associated date and time
 *
*/

#ifndef LOGGER_H
#define LOGGER_H


class Logger
{
private:
    const char* logFilePath = "log.txt";
    const char* parentClassName = "[]";
    bool msgBoxEnabled = false;
public:
    Logger(const char* parentClassName);
    enum messageType {
        INFO,
        WARN,
        CRITICAL
    };
    void log(const char* logStr, messageType msgType, bool msgBox);
};

#endif // LOGGER_H
