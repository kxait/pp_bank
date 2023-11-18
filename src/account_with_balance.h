#ifndef PP_BANK_ACCOUNTWITHBALANCE_H
#define PP_BANK_ACCOUNTWITHBALANCE_H

#include "account_list.h"

class account_with_balance : public account_list::account {
    double m_balance{};
public:
    account_with_balance(account under, double balance);
    double balance() const;
};


#endif //PP_BANK_ACCOUNTWITHBALANCE_H
