#include "Account.h"

#include <utility>

Account::Account(long id, std::string holderName, std::string holderPesel) :
    id(id),
    holderName(std::move(holderName)),
    holderPesel(std::move(holderPesel)) { }


std::string Account::Name() {
    return holderName;
}

std::string Account::Pesel() {
    return holderPesel;
}

long Account::Id() {
    return id;
}
