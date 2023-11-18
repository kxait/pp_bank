#include "config.h"

config::config(std::map<std::string, std::string> conf)
    : m_config(std::move(conf)) {

}

bool config::exists(const std::string&id) {
    const auto v = m_config[id];
    return !v.empty();
}

std::string config::get(const std::string&id) {
    return m_config[id];
}
