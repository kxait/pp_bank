#include "account_list.h"

// zwraca czy konto juz istnialo
bool account_list::add_or_modify_account(const account&t) {
    if(!account_exists(t.id())) {
        m_list.push_back(t);
        return false;
    }

    const auto id = get_account_vector_index(t.id());
    m_list[id] = t;
    return true;
}

long account_list::get_account_vector_index(const long id) const {
    for(long i = 0; i < m_list.size(); i++) {
        if(m_list[i].id() == id) {
            return i;
        }
    }
    return -1;
}

account* account_list::get_account(const long id) {
    if(account_exists(id)) {
        const auto index = get_account_vector_index(id);
        return &(m_list[index]);
    }
    return nullptr;
}

// zwraca czy konto istnialo
bool account_list::delete_account(const long id) {
    if(!account_exists(id)) {
        return false;
    }
    const auto elem = get_account_vector_index(id);
    auto acc = m_list[elem];
    //list.erase(list.begin() + elem);
    m_list[elem] = account(acc.id(), acc.name(), acc.pesel(), true);
    return true;
}

long account_list::get_next_account_id() const {
    long nextId = 1;
    while(account_exists(nextId)) {
        nextId++;
    }
    return nextId;
}

bool account_list::account_exists(const long id) const {
    const auto elem = get_account_vector_index(id);
    if(elem == -1) {
        return false;
    }
    return true;
}

const std::vector<account> *account_list::get_accounts() const {
    return &m_list;
}

account_list::account::account(const long id, std::string holder_name, std::string holder_pesel, const bool deleted)
    : m_id(id),
    m_holder_name(std::move(holder_name)),
    m_holder_pesel(std::move(holder_pesel)),
    m_deleted(deleted) {

}

long account_list::account::id() const {
    return m_id;
}

std::string account_list::account::name() {
    return m_holder_name;
}

std::string account_list::account::pesel() {
    return m_holder_pesel;
}

bool account_list::account::deleted() const {
    return m_deleted;
}
