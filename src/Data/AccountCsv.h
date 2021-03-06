#ifndef PP_BANK_ACCOUNTCSV_H
#define PP_BANK_ACCOUNTCSV_H

#include<vector>
#include "../DALC/AccountDALC.h"
#include "CsvReaderWriter.h"

class AccountCsv : public AccountDALC {
    std::string filename;
    char separator;
public:
    AccountCsv(std::string filename, char separator = ';');
    std::vector<AccountList::Account> getAccounts() override;
    AccountList* getAccountList() override;
    bool saveAccounts(std::vector<AccountList::Account>) override;
    std::string getLocation() override;
};


#endif //PP_BANK_ACCOUNTCSV_H
