#include "logger.h"
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

std::string logger::get_formatted_message(std::string message, log_level_t level) {
    std::string result{m_format};
    std::string lev_str{};
    switch(level) {
        case Info: {
            lev_str = "Info";
            break;
        }
        case Error: {
            lev_str = "Error";
            break;
        }
        default: {
            lev_str = "Unknown";
        }
    }
    auto dt = std::time(nullptr);
    std::stringstream ss{};
    ss << std::put_time(std::localtime(&dt), "%F %T");
    stringReplace(&result, "%D", ss.str());
    stringReplace(&result, "%L", lev_str);
    stringReplace(&result, "%M", message);
    return result;
}

logger::logger(std::string format)
    : m_format(std::move(format)) {

}
