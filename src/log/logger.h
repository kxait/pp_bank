#ifndef PP_BANK_LOGGER_H
#define PP_BANK_LOGGER_H

#include<string>

// format:
// %D - date/time
// %L - level
// %M - message
#define DEFAULT_FORMAT "%D | %L | %M"

class logger {
protected:
    std::string m_format;
public:
    explicit logger(std::string format);
    enum log_level_t {
        Info,
        Error
    };
    virtual void log(log_level_t, std::string message) = 0;
    virtual std::string get_formatted_message(std::string, log_level_t);
};


#endif //PP_BANK_LOGGER_H
