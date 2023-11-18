#ifndef PP_BANK_ACCOUNTCSV_H
#define PP_BANK_ACCOUNTCSV_H

#include<vector>
#include "..\dalc\account_dalc.h"

class account_csv : public account_dalc {
    std::string m_filename;
    char m_separator;
public:
    explicit account_csv(std::string filename, char separator = ';');
    std::vector<account_list::account> get_accounts() override;
    account_list* get_account_list() override;
    bool save_accounts(std::vector<account_list::account>) override;
    std::string get_location() override;
};


#endif //PP_BANK_ACCOUNTCSV_H
