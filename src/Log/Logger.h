#ifndef PP_BANK_LOGGER_H
#define PP_BANK_LOGGER_H

#include<string>

// format:
// %D - data/czas
// %L - poziom
// %M - wiadomosc
#define DEFAULT_FORMAT "%D | %L | %M"

class Logger {
protected:
    std::string format;
public:
    Logger(std::string format);
    enum LogLevel {
        Info,
        Error
    };
    virtual void log(LogLevel, std::string message) = 0;
    virtual std::string getFormattedMessage(std::string, LogLevel);
};


#endif //PP_BANK_LOGGER_H
