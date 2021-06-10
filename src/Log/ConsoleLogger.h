#ifndef PP_BANK_CONSOLELOGGER_H
#define PP_BANK_CONSOLELOGGER_H

#define DEFAULT_CONSOLE_FORMAT "%L: %M"
#include "Logger.h"

class ConsoleLogger : public Logger {
public:
    ConsoleLogger(std::string format = DEFAULT_CONSOLE_FORMAT);
    void log(Logger::LogLevel level, std::string message) override;
};

#endif //PP_BANK_CONSOLELOGGER_H
