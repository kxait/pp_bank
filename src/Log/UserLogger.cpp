#include "UserLogger.h"

#include <sstream>

UserLogger* UserLogger::singleton;

UserLogger::UserLogger() : loggers() {
    singleton = this;
}

void UserLogger::log(Logger::LogLevel level, std::string message) {
    for(auto i : loggers) {
        i->log(level, message);
    }
}

void UserLogger::logInfo(std::string message) {
    log(Logger::LogLevel::Info, message);
}

void UserLogger::logError(std::string message) {
    log(Logger::LogLevel::Error, message);
}

void UserLogger::registerLogger(Logger *logger) {
    loggers.push_back(logger);
}

UserLogger *UserLogger::getLogger() {
    return singleton;
}

std::string UserLogger::getString(std::initializer_list<std::string> a) {
    std::stringstream ss{};
    for(const auto& i : a) {
        ss << i;
    }
    return ss.str();
}
