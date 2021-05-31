#include "Transaction.h"

Transaction::Transaction(long id, long sourceId, long destinationId, double amount) :
        id(id),
        sourceId(sourceId),
        destinationId(destinationId),
        amount(amount) { }

long Transaction::Id() const {
    return id;
}

long Transaction::SourceId() const {
    return sourceId;
}

long Transaction::DestId() const {
    return destinationId;
}

double Transaction::Amount() const {
    return amount;
}
