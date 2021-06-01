#ifndef PP_BANK_ACCOUNTWITHBALANCE_H
#define PP_BANK_ACCOUNTWITHBALANCE_H

#include "AccountList.h"

class AccountWithBalance : public AccountList::Account {
    double balance{};
public:
    AccountWithBalance(AccountList::Account under, double balance);
    double Balance() const;
};


#endif //PP_BANK_ACCOUNTWITHBALANCE_H
