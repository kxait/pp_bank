#include "TransactionFactory.h"
#include "Transaction.h"

TransactionFactory::TransactionFactory(Ledger *ledger) : list(ledger) { }

Transaction TransactionFactory::createTransaction(long sourceId, long destinationId, double amount) {
    if(!isFutureLedgerValid(sourceId, destinationId, amount)) {
        throw std::invalid_argument("ledger invalid after this transaction, aborting");
    }
    long nextId = list->getNextTransactionId();
    Transaction trans(nextId, sourceId, destinationId, amount);
    list->addTransaction(trans);
    return trans;
}

bool TransactionFactory::isFutureLedgerValid(long sourceId, long destinationId, double amount) {
    Ledger copy = *list;
    copy.addTransaction(Transaction(copy.getNextTransactionId(), sourceId, destinationId, amount));
    return copy.isLedgerValid();
}
