#ifndef PP_BANK_TRANSACTIONFACTORY_H
#define PP_BANK_TRANSACTIONFACTORY_H

#include "ledger.h"

class transaction_factory {
    ledger* m_list;
public:
    explicit transaction_factory(ledger* ledger);
    ledger::transaction create_transaction(long source_id, long destination_id, double amount) const;
    bool is_future_ledger_valid(long source_id, long destination_id, double amount) const;
};


#endif //PP_BANK_TRANSACTIONFACTORY_H
