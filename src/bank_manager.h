#ifndef PP_BANK_BANKMANAGER_H
#define PP_BANK_BANKMANAGER_H

#include "account_list.h"
#include "ledger.h"
#include "transaction_factory.h"
#include "dalc\account_dalc.h"
#include "dalc\ledger_dalc.h"
#include "account_with_balance.h"

class bank_manager {
    account_list* m_acc_list = nullptr;
    ledger* m_ledger = nullptr;
    transaction_factory m_transaction_factory;
    account_dalc* m_account_dalc;
    ledger_dalc* m_ledger_dalc;
    void throw_if_ledger_invalid() const;
public:
    bank_manager(ledger_dalc* ledg_dalc, account_dalc* acc_dalc);
    virtual account_list::account* create_account(std::string holder_name, std::string holder_pesel, bool deleted);
    virtual account_list::account* modify_account(long id, std::string holder_name, std::string holder_pesel, bool deleted);
    virtual void delete_account_with_payout(long id);
    virtual void delete_account_with_transfer(long id, long dest_id);
    virtual ledger::transaction create_transaction(long source_id, long dest_id, double amount);
    virtual void save_data();
    virtual void read_data();

    virtual std::vector<account_with_balance> get_account_list();
    std::vector<account_with_balance> get_account_list_skip_deleted() const;
    std::vector<transaction> get_transactions() const;

    virtual double account_balance(long id);

    virtual account_list::account* get_account(long id);
    std::string get_accounts_db_location() const;
    std::string get_ledger_db_location() const;
};


#endif //PP_BANK_BANKMANAGER_H
