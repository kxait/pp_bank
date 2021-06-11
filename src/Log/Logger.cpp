#include "Logger.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
// https://stackoverflow.com/a/3418285
void stringReplace(std::string* str, const std::string& from, const std::string& to) {
    if(from.empty()) {
        return;
    }
    size_t start_pos = 0;
    while((start_pos = str->find(from, start_pos)) != std::string::npos) {
        str->replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string Logger::getFormattedMessage(std::string message, Logger::LogLevel level) {
    std::string result{format};
    std::string levStr{};
    switch(level) {
        case Logger::LogLevel::Info: {
            levStr = "Info";
            break;
        }
        case Logger::LogLevel::Error: {
            levStr = "Error";
            break;
        }
        default: {
            levStr = "Unknown";
        }
    }
    auto dt = std::time(nullptr);
    std::stringstream ss{};
    ss << std::put_time(std::localtime(&dt), "%F %T");
    stringReplace(&result, "%D", ss.str());
    stringReplace(&result, "%L", levStr);
    stringReplace(&result, "%M", message);
    return result;
}

Logger::Logger(std::string format)
    : format(std::move(format)) {

}
