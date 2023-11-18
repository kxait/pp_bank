#ifndef PP_BANK_FILELOGGER_H
#define PP_BANK_FILELOGGER_H

#include "logger.h"
#include <fstream>
#include <string>

class FileLogger : public Logger {
    std::string filename;
    std::ofstream fileHandle;
public:
    FileLogger(std::string file, std::string format = DEFAULT_FORMAT);
    void log(Logger::LogLevel level, std::string message) override;
    ~FileLogger();
};


#endif //PP_BANK_FILELOGGER_H
