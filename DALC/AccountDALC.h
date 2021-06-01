#ifndef PP_BANK_ACCOUNTDALC_H
#define PP_BANK_ACCOUNTDALC_H


#include <vector>
#include "../AccountList.h"

class AccountDALC {
public:
    virtual std::vector<AccountList::Account> getAccounts() = 0;
    virtual AccountList* getAccountList() = 0;
    virtual bool saveAccounts(std::vector<AccountList::Account>) = 0;
};


#endif //PP_BANK_ACCOUNTDALC_H
