#include "ConsoleLogger.h"
#include<iostream>

ConsoleLogger::ConsoleLogger(std::string format)
    : Logger(format) {;
}

void ConsoleLogger::log(Logger::LogLevel level, std::string message) {
    auto m = Logger::getFormattedMessage(message, level);
    std::cout << m << std::endl;
}
