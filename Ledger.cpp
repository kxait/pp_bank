#include "Ledger.h"

// nowe id aby nie bylo kolizji
bool Ledger::addTransaction(Transaction t) {
    Transaction newT(getNextTransactionId(), t.SourceId(), t.DestId(), t.Amount());
    ledger.push_back(newT);
    return false;
}

Transaction* Ledger::getTransaction(long id) {
    long index = getTransactionId(id);
    if(index == -1) {
        return nullptr;
    }
    return &(ledger[index]);
}

long Ledger::getTransactionId(long id) {
    for(long i = 0; i < ledger.size(); i++) {
        if(ledger[i].Id() == id) {
            return i;
        }
    }
    return -1;
}

double Ledger::getBalance(long accountId) {
    auto balanceSheet = getBalanceSheet();
    if(balanceSheet.find(accountId) == balanceSheet.end()) {
        return 0;
    }
    return balanceSheet[accountId];
}

// zaklada ze lista tranzakcji jest ciagla
long Ledger::getNextTransactionId() {
    return ledger.size();
}

bool Ledger::isLedgerValid() {
    auto balanceSheet = getBalanceSheet();

    for(auto trans : balanceSheet) {
        if(trans.second < 0 && trans.first != 0) { // drugi warunek - konto nie jest okienkiem
            // lista jest niepoprawna - ktos ma ujemne saldo
            return false;
        }
    }

    return true;
}

Ledger::Ledger(const Ledger& other) {
    for(auto i : other.ledger) {
        addTransaction(Transaction(i.Id(), i.SourceId(), i.DestId(), i.Amount()));
    }
}

long Ledger::transQty() {
    return ledger.size();
}

Ledger::Ledger() {

}

std::map<long, double> Ledger::getBalanceSheet() {
    std::map<long, double> balanceSheet{};

    for(auto trans : ledger) {
        if(balanceSheet.find(trans.SourceId()) == balanceSheet.end()) {
            balanceSheet[trans.SourceId()] = 0;
        }
        if(balanceSheet.find(trans.DestId()) == balanceSheet.end()) {
            balanceSheet[trans.DestId()] = 0;
        }

        balanceSheet[trans.SourceId()] -= trans.Amount();
        balanceSheet[trans.DestId()] += trans.Amount();
    }

    return balanceSheet;
}

const std::vector<Transaction> *Ledger::getTransactions() {
    return new std::vector<Transaction>{ledger};
}
