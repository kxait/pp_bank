#ifndef PP_BANK_ACCOUNTMOCK_H
#define PP_BANK_ACCOUNTMOCK_H

#include<vector>
#include "../DALC/AccountDALC.h"

class AccountMock : public AccountDALC {
    static std::vector<Account> data;
public:
    std::vector<Account> getAccounts() override;
    AccountList* getAccountList() override;
    bool saveAccounts(std::vector<Account>) override;
    std::string getLocation() override;
};


#endif //PP_BANK_ACCOUNTMOCK_H
