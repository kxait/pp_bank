#ifndef PP_BANK_BANKMANAGER_H
#define PP_BANK_BANKMANAGER_H

#include "AccountList.h"
#include "Ledger.h"
#include "TransactionFactory.h"
#include "DALC/AccountDALC.h"
#include "DALC/LedgerDALC.h"
#include "AccountWithBalance.h"

class BankManager {
    AccountList* accList = nullptr;
    Ledger* ledger = nullptr;
    TransactionFactory transFac;
    AccountDALC* accDalc;
    LedgerDALC* ledgDalc;
    void throwIfLedgerInvalid();
public:
    BankManager(LedgerDALC* ledgDalc, AccountDALC* accDalc);
    virtual AccountList::Account* createAccount(std::string holderName, std::string holderPesel, bool deleted);
    virtual AccountList::Account* modifyAccount(long id, std::string holderName, std::string holderPesel, bool deleted);
    virtual void deleteAccountWithPayout(long id);
    virtual void deleteAccountWithTransfer(long id, long destId);
    virtual Ledger::Transaction createTransaction(long sourceId, long destId, double amount);
    virtual void saveData();
    virtual void readData();
    std::vector<AccountWithBalance> getAccountList();
    std::vector<AccountWithBalance> getAccountListSkipDeleted();
    std::vector<Transaction> getTransactions();
    double accountBalance(long id);
    AccountList::Account* getAccount(long id);
    std::string getAccountsDbLocation();
    std::string getLedgerDbLocation();
};


#endif //PP_BANK_BANKMANAGER_H
