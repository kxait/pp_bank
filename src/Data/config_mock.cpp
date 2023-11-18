#include "config_mock.h"

std::map<std::string, std::string> ConfigMock::data{
        {"ledger_db_location", "mock"},
        {"accounts_db_location", "mock"}
};

std::map<std::string, std::string> ConfigMock::getData() {
    return data;
}

Config *ConfigMock::getConfig() {
    return new Config(data);
}

std::string ConfigMock::getLocation() {
    return "mock";
}
