#ifndef PP_BANK_BANKMANAGERLOGGER_H
#define PP_BANK_BANKMANAGERLOGGER_H

#include "bank_manager.h"
#include "account_list.h"
#include "ledger.h"
#include "transaction_factory.h"
#include "DALC\account_dalc.h"
#include "DALC\ledger_dalc.h"
#include "account_with_balance.h"
#include "Log\user_logger.h"

// dodatkowo lapie wyjatki
class BankManagerLogger : public BankManager {
    UserLogger* logger;
public:
    BankManagerLogger(LedgerDALC* ledgDalc, AccountDALC* accDalc, UserLogger* logger);
    AccountList::Account* createAccount(std::string holderName, std::string holderPesel, bool deleted);
    AccountList::Account* modifyAccount(long id, std::string holderName, std::string holderPesel, bool deleted);
    void deleteAccountWithPayout(long id);
    void deleteAccountWithTransfer(long id, long destId);
    Ledger::Transaction createTransaction(long sourceId, long destId, double amount);
    void saveData();
    void readData();
    std::vector<AccountWithBalance> getAccountList();
    double accountBalance(long id);
    AccountList::Account* getAccount(long id);
};


#endif //PP_BANK_BANKMANAGERLOGGER_H
