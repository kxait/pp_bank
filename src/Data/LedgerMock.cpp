#include "LedgerMock.h"

std::vector<Ledger::Transaction> LedgerMock::data = {
        Ledger::Transaction(0, 0, 1, 4.2),
        Ledger::Transaction(1, 1, 2, 2.0),
        Ledger::Transaction(2, 0, 3, 10.0),
        Ledger::Transaction(3, 3, 1, 1.0),
        Ledger::Transaction(4, 3, 0, 5)
};

std::vector<Ledger::Transaction> LedgerMock::getTransactions() {
    return data;
}

bool LedgerMock::saveTransactions(std::vector<Ledger::Transaction> transactions) {
    data = transactions;
    return true;
}

Ledger *LedgerMock::getLedger() {
    auto list = new Ledger();
    for(auto i : data) {
        list->addTransaction(i);
    }
    return list;
}

std::string LedgerMock::getLocation() {
    return "mock";
}
