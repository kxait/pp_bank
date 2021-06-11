#ifndef PP_BANK_BANKMANAGERLOGGER_H
#define PP_BANK_BANKMANAGERLOGGER_H

#include "BankManager.h"
#include "AccountList.h"
#include "Ledger.h"
#include "TransactionFactory.h"
#include "DALC/AccountDALC.h"
#include "DALC/LedgerDALC.h"
#include "AccountWithBalance.h"
#include "Log/UserLogger.h"

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
