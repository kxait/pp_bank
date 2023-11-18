#ifndef PP_BANK_CONSOLELOGGER_H
#define PP_BANK_CONSOLELOGGER_H

#define DEFAULT_CONSOLE_FORMAT "%L: %M"
#include "logger.h"

class console_logger : public logger {
public:
    explicit console_logger(const std::string&format = DEFAULT_CONSOLE_FORMAT);
    void log(log_level_t level, std::string message) override;
};

#endif //PP_BANK_CONSOLELOGGER_H
