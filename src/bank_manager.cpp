#include "bank_manager.h"

#include "dalc\ledger_dalc.h"
#include "dalc\account_dalc.h"

bank_manager::bank_manager(ledger_dalc* ledg_dalc, account_dalc* acc_dalc)
    : m_transaction_factory(nullptr),
    m_ledger_dalc(ledg_dalc),
    m_account_dalc(acc_dalc) {
    read_data();
    m_transaction_factory = transaction_factory(m_ledger);
}

account_list::account* bank_manager::create_account(std::string holder_name, std::string holder_pesel, const bool deleted) {
    return modify_account(m_acc_list->get_next_account_id(), std::move(holder_name), std::move(holder_pesel), deleted);
}

account_list::account* bank_manager::modify_account(const long id, std::string holder_name, std::string holder_pesel, const bool deleted) {
    const auto acc = new account_list::account(id, std::move(holder_name), std::move(holder_pesel), deleted);
    m_acc_list->add_or_modify_account(*acc);
    return acc;
}

void bank_manager::delete_account_with_payout(const long id) {
    delete_account_with_transfer(id, 0);
}

void bank_manager::delete_account_with_transfer(const long id, const long dest_id) {
    const auto trans_acc = m_ledger->get_balance(id);
    const auto acc = m_acc_list->get_account(id);
    if(trans_acc == -1 || acc == nullptr) {
        throw std::out_of_range("account doesnt exist");
    }

    if(trans_acc != 0) {
        create_transaction(acc->id(), dest_id, m_ledger->get_balance(id));
    }
    m_acc_list->delete_account(id);
}

// rzuci wyjatek jesli transakcja jest niepoprawna
ledger::transaction bank_manager::create_transaction(const long source_id, const long dest_id, const double amount) {
    const auto accounts_exist =
        m_acc_list->account_exists(source_id)
        && m_acc_list->account_exists(dest_id);
    const auto source_acc_deleted_or_dest_acc_deleted = accounts_exist &&
                                                        (m_acc_list->get_account(source_id)->deleted()
                                                         || m_acc_list->get_account(dest_id)->deleted());
    if(m_acc_list->account_exists(source_id)
        && m_acc_list->account_exists(dest_id)
        && amount != 0
        && !source_acc_deleted_or_dest_acc_deleted
        && accounts_exist) {
        const auto trans = m_transaction_factory.create_transaction(source_id, dest_id, amount);
        return trans;
    }
    throw std::runtime_error("nie udalo sie stworzyc transakcji z zlymi danymi");
}

void bank_manager::save_data() {
    throw_if_ledger_invalid();

    auto a = const_cast<std::vector<ledger::transaction>*>(m_ledger->get_transactions());
    m_ledger_dalc->save_transactions(*a);

    auto b = const_cast<std::vector<account_list::account>*>(m_acc_list->get_accounts());
    m_account_dalc->save_accounts(*b);
}

void bank_manager::read_data() {
    account_list* new_account_list;
    try {
        new_account_list = m_account_dalc->get_account_list();
    }catch(const std::exception& e) {
        throw std::runtime_error("nie udalo sie przeczytac listy kont");
    }

    const auto old_account_list = m_acc_list;
    m_acc_list = new_account_list;

    ledger* new_ledger;
    try {
        new_ledger = m_ledger_dalc->get_ledger();
    }catch(const std::exception& e) {
        m_acc_list = old_account_list;
        throw std::runtime_error("nie udalo sie przeczytac listy transakcji");
    }
    if(!new_ledger->is_ledger_valid()) {
        m_acc_list = old_account_list;
        throw std::runtime_error("nowa lista transakcji byla niepoprawna");
    }

    if(m_ledger != nullptr) {
        delete m_ledger;
    }
    m_ledger = new_ledger;
    m_transaction_factory = transaction_factory(m_ledger);

    delete old_account_list;
}

double bank_manager::account_balance(const long id) {
    return m_ledger->get_balance(id);
}

account_list::account *bank_manager::get_account(const long id) {
    return m_acc_list->get_account(id);
}

std::vector<account_with_balance> bank_manager::get_account_list() {
    const auto accs = m_acc_list->get_accounts();
    std::vector<account_with_balance> with_balances{};
    for(const auto& acc : *accs) {
        const auto bal = m_ledger->get_balance(acc.id());
        account_with_balance a(acc, bal);
        with_balances.push_back(a);
    }
    return with_balances;
}

std::vector<account_with_balance> bank_manager::get_account_list_skip_deleted() const {
    auto accs = m_acc_list->get_accounts();
    std::vector<account_with_balance> accsBalances{};
    for(auto acc : *accs) {
        if(acc.deleted()) {
            continue;
        }
        const auto bal = m_ledger->get_balance(acc.id());
        account_with_balance a(acc, bal);
        accsBalances.push_back(a);
    }
    return accsBalances;
}

void bank_manager::throw_if_ledger_invalid() const {
    if(!m_ledger->is_ledger_valid()) {
        throw std::runtime_error("lista transakcji byla niepoprawna podczas sprawdzenia");
    }
}

std::vector<transaction> bank_manager::get_transactions() const {
    auto transactions = *m_ledger->get_transactions();
    return transactions;
}

std::string bank_manager::get_accounts_db_location() const {
    return m_account_dalc->get_location();
}

std::string bank_manager::get_ledger_db_location() const {
    return m_ledger_dalc->get_location();
}
