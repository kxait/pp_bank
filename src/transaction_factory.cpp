#include "transaction_factory.h"

transaction_factory::transaction_factory(ledger *ledger) : m_list(ledger) { }

ledger::transaction transaction_factory::create_transaction(const long source_id, const long destination_id, const double amount) const {
    if(source_id == destination_id || amount == 0) {
        throw std::invalid_argument("niepoprawna transakcja");
    }

    if(!is_future_ledger_valid(source_id, destination_id, amount)) {
        throw std::invalid_argument("lista transakcji byla niepoprawna po nowej transakcji");
    }
    const long next_id = m_list->get_next_transaction_id();
    const ledger::transaction trans(next_id, source_id, destination_id, amount);
    m_list->add_transaction(trans);
    return trans;
}

bool transaction_factory::is_future_ledger_valid(const long source_id, const long destination_id, const double amount) const {
    ledger copy = *m_list;
    copy.add_transaction(ledger::transaction(copy.get_next_transaction_id(), source_id, destination_id, amount));
    return copy.is_ledger_valid();
}
