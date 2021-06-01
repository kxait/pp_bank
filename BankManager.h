//
// Created by Tomek Osika on 25/05/2021.
//

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
    Account* createAccount(std::string holderName, std::string holderPesel);
    Account* modifyAccount(long id, std::string holderName, std::string holderPesel);
    void deleteAccountWithPayout(long id);
    void deleteAccountWithTransfer(long id, long destId);
    Transaction createTransaction(long sourceId, long destId, double amount);
    void saveData();
    void readData();
    std::vector<AccountWithBalance> getAccountList();
    double accountBalance(long id);
    Account* getAccount(long id);
};


#endif //PP_BANK_BANKMANAGER_H
