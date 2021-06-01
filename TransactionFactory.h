#ifndef PP_BANK_TRANSACTIONFACTORY_H
#define PP_BANK_TRANSACTIONFACTORY_H


#include "Ledger.h"

class TransactionFactory {
    Ledger* list;
public:
    TransactionFactory(Ledger* ledger);
    Transaction createTransaction(long sourceId, long destinationId, double amount);
    bool isFutureLedgerValid(long sourceId, long destinationId, double amount);
};


#endif //PP_BANK_TRANSACTIONFACTORY_H
