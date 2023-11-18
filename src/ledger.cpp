#include "ledger.h"

// nowe id aby nie bylo kolizji
bool ledger::add_transaction(const transaction&t) {
    const transaction new_t(get_next_transaction_id(), t.source_id(), t.dest_id(), t.amount());
    m_ledger.push_back(new_t);
    return false;
}

ledger::transaction* ledger::get_transaction(const long id) {
    const long index = get_transaction_id(id);
    if(index == -1) {
        return nullptr;
    }
    return &(m_ledger[index]);
}

long ledger::get_transaction_id(const long id) const {
    for(long i = 0; i < m_ledger.size(); i++) {
        if(m_ledger[i].id() == id) {
            return i;
        }
    }
    return -1;
}

double ledger::get_balance(const long account_id) {
    auto balance_sheet = get_balance_sheet();
    if(balance_sheet.find(account_id) == balance_sheet.end()) {
        return 0;
    }
    return balance_sheet[account_id];
}

// zaklada ze lista tranzakcji jest ciagla
long ledger::get_next_transaction_id() const {
    return m_ledger.size();
}

bool ledger::is_ledger_valid() {
    const auto balance_sheet = get_balance_sheet();

    for(const auto trans : balance_sheet) {
        if(trans.second < 0 && trans.first != 0) { // drugi warunek - konto nie jest okienkiem
            // lista jest niepoprawna - ktos ma ujemne saldo
            return false;
        }
    }

    return true;
}

long ledger::trans_qty() const {
    return m_ledger.size();
}

std::map<long, double> ledger::get_balance_sheet() const {
    std::map<long, double> balance_sheet{};

    for(auto trans : m_ledger) {
        if(balance_sheet.find(trans.source_id()) == balance_sheet.end()) {
            balance_sheet[trans.source_id()] = 0;
        }
        if(balance_sheet.find(trans.dest_id()) == balance_sheet.end()) {
            balance_sheet[trans.dest_id()] = 0;
        }

        balance_sheet[trans.source_id()] -= trans.amount();
        balance_sheet[trans.dest_id()] += trans.amount();
    }

    return balance_sheet;
}

const std::vector<ledger::transaction> *ledger::get_transactions() const {
    return new std::vector<transaction>{m_ledger};
}

ledger::ledger() {

}

ledger::transaction::transaction(const long id, const long source_id, const long destination_id, const double amount) :
        m_id(id),
        m_source_id(source_id),
        m_destination_id(destination_id),
        m_amount(amount) { }

long ledger::transaction::id() const {
    return m_id;
}

long ledger::transaction::source_id() const {
    return m_source_id;
}

long ledger::transaction::dest_id() const {
    return m_destination_id;
}

double ledger::transaction::amount() const {
    return m_amount;
}

