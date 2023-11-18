#ifndef PP_BANK_ACCOUNTDALC_H
#define PP_BANK_ACCOUNTDALC_H


#include <vector>
#include "../account_list.h"

class account_dalc {
public:
    virtual std::vector<account_list::account> get_accounts() = 0;
    virtual account_list* get_account_list() = 0;
    virtual bool save_accounts(std::vector<account_list::account>) = 0;
    virtual std::string get_location() = 0;
};


#endif //PP_BANK_ACCOUNTDALC_H
