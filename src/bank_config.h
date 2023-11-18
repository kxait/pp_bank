#ifndef PP_BANK_BANKCONFIG_H
#define PP_BANK_BANKCONFIG_H

#include <string>
#include "DALC\config_dalc.h"

class BankConfig {
    std::string ledgerDbLocation;
    std::string accountsDbLocation;
    ConfigDALC* config;
    void getConfig();
public:
    BankConfig(ConfigDALC*);
    std::string LedgerDbLocation();
    std::string AccountsDbLocation();
};


#endif //PP_BANK_BANKCONFIG_H
