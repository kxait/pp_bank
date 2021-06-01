#include "AccountWithBalance.h"

AccountWithBalance::AccountWithBalance(AccountList::Account under, double balance)
    : AccountList::Account(under.Id(), under.Name(), under.Pesel()),
    balance(balance) {

}

double AccountWithBalance::Balance() const {
    return balance;
}
