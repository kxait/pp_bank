#include <iostream>
#include <vector>
#include "Transaction.h"
#include <map>

#ifndef PP_BANK_LEDGER_H
#define PP_BANK_LEDGER_H

class Ledger {
    std::vector<Transaction> ledger;
public:
    Ledger();
    Ledger(const Ledger& other);
    bool addTransaction(Transaction t);
    long getTransactionId(long id);
    Transaction* getTransaction(long id);
    const std::vector<Transaction>* getTransactions();
    double getBalance(long accountId);
    long getNextTransactionId();
    bool isLedgerValid();
    long transQty();
    std::map<long, double> getBalanceSheet();
};


#endif //PP_BANK_LEDGER_H
