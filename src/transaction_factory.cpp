#include "transaction_factory.h"

TransactionFactory::TransactionFactory(Ledger *ledger) : list(ledger) { }

Ledger::Transaction TransactionFactory::createTransaction(long sourceId, long destinationId, double amount) {
    if(sourceId == destinationId || amount == 0) {
        throw std::invalid_argument("niepoprawna transakcja");
    }

    if(!isFutureLedgerValid(sourceId, destinationId, amount)) {
        throw std::invalid_argument("lista transakcji byla niepoprawna po nowej transakcji");
    }
    long nextId = list->getNextTransactionId();
    Ledger::Transaction trans(nextId, sourceId, destinationId, amount);
    list->addTransaction(trans);
    return trans;
}

bool TransactionFactory::isFutureLedgerValid(long sourceId, long destinationId, double amount) {
    Ledger copy = *list;
    copy.addTransaction(Ledger::Transaction(copy.getNextTransactionId(), sourceId, destinationId, amount));
    return copy.isLedgerValid();
}
