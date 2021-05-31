#include "Account.h"
#include<iostream>
#include<vector>

#ifndef PP_BANK_ACCOUNTLIST_H
#define PP_BANK_ACCOUNTLIST_H


class AccountList {
    std::vector<Account> list;
public:
    bool addOrModifyAccount(Account t);
    long getAccountVectorIndex(long id);
    Account* getAccount(long id);
    bool deleteAccount(long id);
    long getNextAccountId();
    bool accountExists(long id);
    const std::vector<Account>* getAccounts();
};


#endif //PP_BANK_ACCOUNTLIST_H
