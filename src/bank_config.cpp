#include "bank_config.h"

void bank_config::get_config() {
    const auto conf = m_config->get_config();

    if(!conf->exists("ledger_db_location")) {
        throw std::runtime_error("nie znaleziono w pliku konfiguracyjnym wartosci dla ledger_db_location");
    }

    if(!conf->exists("accounts_db_location")) {
        throw std::runtime_error("nie znaleziono w pliku konfiguracyjnym wartosci dla accounts_db_location");
    }

    m_ledger_db_location = conf->get("ledger_db_location");
    m_accounts_db_location = conf->get("accounts_db_location");
}

bank_config::bank_config(config_dalc* config)
    :m_config(config) {
    get_config();
}

std::string bank_config::ledger_db_location() {
    return m_ledger_db_location;
}

std::string bank_config::accounts_db_location() {
    return m_accounts_db_location;
}
