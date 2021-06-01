#include "LedgerMock.h"

std::vector<Transaction> LedgerMock::data = {
        Transaction(0, 0, 1, 4.2),
        Transaction(1, 1, 2, 2.0),
        Transaction(2, 0, 3, 10.0),
        Transaction(3, 3, 1, 1.0),
        Transaction(4, 3, 0, 5)
};

std::vector<Transaction> LedgerMock::getTransactions() {
    return data;
}

bool LedgerMock::saveTransactions(std::vector<Transaction> transactions) {
    data = std::vector<Transaction>(transactions);
    return true;
}

Ledger *LedgerMock::getLedger() {
    auto list = new Ledger();
    for(auto i : data) {
        list->addTransaction(i);
    }
    return list;
}
