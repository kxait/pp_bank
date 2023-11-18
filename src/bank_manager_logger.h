#ifndef PP_BANK_BANKMANAGERLOGGER_H
#define PP_BANK_BANKMANAGERLOGGER_H

#include "bank_manager.h"
#include "account_list.h"
#include "ledger.h"
#include "dalc\account_dalc.h"
#include "dalc\ledger_dalc.h"
#include "account_with_balance.h"
#include "log\user_logger.h"

// also catches exceptions
class bank_manager_logger : public bank_manager {
    user_logger* m_logger;
public:
    bank_manager_logger(ledger_dalc* ledg_dalc, account_dalc* acc_dalc, user_logger* logger);
    account_list::account* create_account(std::string holder_name, std::string holder_pesel, bool deleted) override;
    account_list::account* modify_account(long id, std::string holder_name, std::string holder_pesel, bool deleted) override;
    void delete_account_with_payout(long id) override;
    void delete_account_with_transfer(long id, long dest_id) override;
    ledger::transaction create_transaction(long source_id, long dest_id, double amount) override;
    void save_data() override;
    void read_data() override;
    std::vector<account_with_balance> get_account_list() override;
    double account_balance(long id) override;
    account_list::account* get_account(long id) override;
};


#endif //PP_BANK_BANKMANAGERLOGGER_H
