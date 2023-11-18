#include "console_logger.h"
#include<iostream>

console_logger::console_logger(const std::string&format)
    : logger(format) {;
}

void console_logger::log(const log_level_t level, const std::string message) {
    const auto m = logger::get_formatted_message(message, level);
    std::cout << m << std::endl;
}
