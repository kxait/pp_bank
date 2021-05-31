#include<iostream>

#ifndef PP_BANK_ACCOUNT_H
#define PP_BANK_ACCOUNT_H


class Account {
protected:
    long id;
    std::string holderName;
    std::string holderPesel;
public:
    Account(long id, std::string holderName, std::string holderPesel);
    long Id();
    std::string Name();
    std::string Pesel();
};


#endif //PP_BANK_ACCOUNT_H
