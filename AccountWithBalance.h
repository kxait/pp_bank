#ifndef PP_BANK_ACCOUNTWITHBALANCE_H
#define PP_BANK_ACCOUNTWITHBALANCE_H


#include "Account.h"

class AccountWithBalance : public Account {
    double balance{};
public:
    AccountWithBalance(Account under, double balance);
    double Balance() const;
};


#endif //PP_BANK_ACCOUNTWITHBALANCE_H
