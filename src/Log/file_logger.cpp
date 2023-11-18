#include "file_logger.h"
#include<iostream>

FileLogger::FileLogger(std::string file, std::string format)
    : Logger(std::move(format)),
      filename(std::move(file)),
      fileHandle(filename, std::ofstream::out | std::ofstream::app) {
    if(!fileHandle.is_open()) {
        throw std::runtime_error("nie udalo sie otworzyc pliku");
    }
}

void FileLogger::log(Logger::LogLevel level, std::string message) {
    auto m = Logger::getFormattedMessage(message, level);
    fileHandle << m << std::endl;
}

FileLogger::~FileLogger() {
    fileHandle.close();
}
