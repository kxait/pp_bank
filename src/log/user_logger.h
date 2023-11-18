#ifndef PP_BANK_USERLOGGER_H
#define PP_BANK_USERLOGGER_H


//#define DEBUG

#include <vector>
#include "logger.h"
#include <initializer_list>

class user_logger {
    std::vector<logger*> m_loggers;
    static user_logger* m_singleton;
public:
    user_logger();
    void log(logger::log_level_t level, const std::string&message) const;
    void log_info(const std::string&message) const;
    void log_error(const std::string&message) const;
    void register_logger(logger* logger);
    static user_logger* get_logger();
    static std::string get_string(std::initializer_list<std::string>);
public:
};


#endif //PP_BANK_USERLOGGER_H
