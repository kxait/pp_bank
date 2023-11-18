#ifndef PP_BANK_FILELOGGER_H
#define PP_BANK_FILELOGGER_H

#include "logger.h"
#include <fstream>
#include <string>

class file_logger : public logger {
    std::string m_filename;
    std::ofstream m_file_handle;
public:
    explicit file_logger(std::string file, std::string format = DEFAULT_FORMAT);
    void log(log_level_t level, std::string message) override;
    ~file_logger();
};


#endif //PP_BANK_FILELOGGER_H
