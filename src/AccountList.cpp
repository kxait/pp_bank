#include "AccountList.h"

// zwraca czy konto juz istnialo
bool AccountList::addOrModifyAccount(Account t) {
    if(!accountExists(t.Id())) {
        list.push_back(t);
        return false;
    }

    auto id = getAccountVectorIndex(t.Id());
    list[id] = t;
    return true;
}

long AccountList::getAccountVectorIndex(long id) {
    for(long i = 0; i < list.size(); i++) {
        if(list[i].Id() == id) {
            return i;
        }
    }
    return -1;
}

Account* AccountList::getAccount(long id) {
    if(accountExists(id)) {
        auto index = getAccountVectorIndex(id);
        return &(list[index]);
    }
    return nullptr;
}

// zwraca czy konto istnialo
bool AccountList::deleteAccount(long id) {
    if(!accountExists(id)) {
        return false;
    }
    auto elem = getAccountVectorIndex(id);
    list.erase(list.begin() + elem);
    return true;
}

long AccountList::getNextAccountId() {
    long nextId = 1;
    while(accountExists(nextId)) {
        nextId++;
    }
    return nextId;
}

bool AccountList::accountExists(long id) {
    auto elem = getAccountVectorIndex(id);
    if(elem == -1) {
        return false;
    }
    return true;
}

const std::vector<Account> *AccountList::getAccounts() {
    return const_cast<const std::vector<Account>*>(&list);
}

AccountList::Account::Account(long id, std::string holderName, std::string holderPesel)
    : id(id),
    holderName(std::move(holderName)),
    holderPesel(std::move(holderPesel)) {

}

long AccountList::Account::Id() {
    return id;
}

std::string AccountList::Account::Name() {
    return holderName;
}

std::string AccountList::Account::Pesel() {
    return holderPesel;
}
