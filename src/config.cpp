#include "config.h"

Config::Config(std::map<std::string, std::string> conf)
    : config(conf) {

}

bool Config::exists(std::string id) {
    auto v = config[id];
    return !v.empty();
}

std::string Config::get(std::string id) {
    return config[id];
}
