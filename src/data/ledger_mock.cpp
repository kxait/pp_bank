#include "ledger_mock.h"

#include <string>

std::vector<ledger::transaction> ledger_mock::m_data = {
        ledger::transaction(0, 0, 1, 4.2),
        ledger::transaction(1, 1, 2, 2.0),
        ledger::transaction(2, 0, 3, 10.0),
        ledger::transaction(3, 3, 1, 1.0),
        ledger::transaction(4, 3, 0, 5)
};

std::vector<ledger::transaction> ledger_mock::get_transactions() {
    return m_data;
}

bool ledger_mock::save_transactions(const std::vector<ledger::transaction> transactions) {
    m_data = transactions;
    return true;
}

ledger *ledger_mock::get_ledger() {
    const auto list = new ledger();
    for(auto i : m_data) {
        list->add_transaction(i);
    }
    return list;
}

std::string ledger_mock::get_location() {
    return "mock";
}
