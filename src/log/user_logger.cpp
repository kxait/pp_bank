#include "user_logger.h"

#include <sstream>

user_logger* user_logger::m_singleton;

user_logger::user_logger() {
    m_singleton = this;
}

void user_logger::log(const logger::log_level_t level, const std::string&message) const {
    for(auto i : m_loggers) {
        i->log(level, message);
    }
}

void user_logger::log_info(const std::string&message) const {
    log(logger::log_level_t::Info, message);
}

void user_logger::log_error(const std::string&message) const {
    log(logger::log_level_t::Error, message);
}

void user_logger::register_logger(logger *logger) {
    m_loggers.push_back(logger);
}

user_logger *user_logger::get_logger() {
    return m_singleton;
}

std::string user_logger::get_string(const std::initializer_list<std::string> a) {
    std::stringstream ss{};
    for(const auto& i : a) {
        ss << i;
    }
    return ss.str();
}
