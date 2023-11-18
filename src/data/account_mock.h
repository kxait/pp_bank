#ifndef PP_BANK_ACCOUNTMOCK_H
#define PP_BANK_ACCOUNTMOCK_H

#include<vector>
#include "..\dalc\account_dalc.h"

class account_mock : public account_dalc {
    static std::vector<account> m_data;
public:
    std::vector<account> get_accounts() override;
    account_list* get_account_list() override;
    bool save_accounts(std::vector<account>) override;
    std::string get_location() override;
};


#endif //PP_BANK_ACCOUNTMOCK_H
