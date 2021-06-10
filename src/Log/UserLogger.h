#ifndef PP_BANK_USERLOGGER_H
#define PP_BANK_USERLOGGER_H


//#define DEBUG

#include <vector>
#include "Logger.h"
#include <initializer_list>

class UserLogger {
    std::vector<Logger*> loggers;
    static UserLogger* singleton;
public:
    UserLogger();
    void log(Logger::LogLevel level, std::string message);
    void logInfo(std::string message);
    void logError(std::string message);
    void registerLogger(Logger* logger);
    static UserLogger* getLogger();
    static std::string getString(std::initializer_list<std::string>);
public:
};


#endif //PP_BANK_USERLOGGER_H
