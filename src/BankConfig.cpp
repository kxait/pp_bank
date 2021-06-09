#include "BankConfig.h"

void BankConfig::getConfig() {
    auto conf = config->getConfig();

    if(!conf->exists("ledger_db_location")) {
        throw std::runtime_error("nie znaleziono w pliku konfiguracyjnym wartosci dla ledger_db_location");
    }

    if(!conf->exists("accounts_db_location")) {
        throw std::runtime_error("nie znaleziono w pliku konfiguracyjnym wartosci dla accounts_db_location");
    }

    ledgerDbLocation = conf->get("ledger_db_location");
    accountsDbLocation = conf->get("accounts_db_location");
}

BankConfig::BankConfig(ConfigDALC* config)
    :config(config) {
    getConfig();
}

std::string BankConfig::LedgerDbLocation() {
    return ledgerDbLocation;
}

std::string BankConfig::AccountsDbLocation() {
    return accountsDbLocation;
}
