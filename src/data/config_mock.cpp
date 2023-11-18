#include "config_mock.h"

std::map<std::string, std::string> config_mock::m_data{
        {"ledger_db_location", "mock"},
        {"accounts_db_location", "mock"}
};

std::map<std::string, std::string> config_mock::get_data() {
    return m_data;
}

config *config_mock::get_config() {
    return new config(m_data);
}

std::string config_mock::get_location() {
    return "mock";
}
