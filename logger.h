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
public:
    enum messageType {
        INFO,
        WARN,
        CRITICAL
    };
    void log(const char* logStr, messageType msgType = INFO);
};

#endif // LOGGER_H
