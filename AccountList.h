#ifndef PP_BANK_ACCOUNTLIST_H
#define PP_BANK_ACCOUNTLIST_H

#include<iostream>
#include<vector>

class AccountList {
public:
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

    bool addOrModifyAccount(Account t);
    long getAccountVectorIndex(long id);
    Account* getAccount(long id);
    bool deleteAccount(long id);
    long getNextAccountId();
    bool accountExists(long id);
    const std::vector<Account>* getAccounts();
private:
    std::vector<Account> list;
};

typedef AccountList::Account Account;


#endif //PP_BANK_ACCOUNTLIST_H
