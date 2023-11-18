#ifndef PP_BANK_BANKCONFIG_H
#define PP_BANK_BANKCONFIG_H

#include <string>
#include "dalc/config_dalc.h"

class bank_config {
    std::string m_ledger_db_location;
    std::string m_accounts_db_location;
    config_dalc* m_config{};
    void get_config();
public:
    explicit bank_config(config_dalc*);
    std::string ledger_db_location();
    std::string accounts_db_location();
};


#endif //PP_BANK_BANKCONFIG_H
