#ifndef PP_BANK_LEDGER_H
#define PP_BANK_LEDGER_H

#include <iostream>
#include <vector>
#include <map>


class Ledger {
public:
    class Transaction {
        long id;
        long sourceId;
        long destinationId;
        double amount;
    public:
        Transaction(long id, long sourceId, long destinationId, double amount);
        long Id() const;
        long SourceId() const;
        long DestId() const;
        double Amount() const;
    };
    Ledger();
    Ledger(const Ledger& other);
    bool addTransaction(Ledger::Transaction t);
    long getTransactionId(long id);
    Transaction* getTransaction(long id);
    const std::vector<Transaction>* getTransactions();
    double getBalance(long accountId);
    long getNextTransactionId();
    bool isLedgerValid();
    long transQty();
    std::map<long, double> getBalanceSheet();
private:
    std::vector<Transaction> ledger{};

};

typedef Ledger::Transaction Transaction;

#endif //PP_BANK_LEDGER_H
