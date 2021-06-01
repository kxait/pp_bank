#include "AccountWithBalance.h"

AccountWithBalance::AccountWithBalance(Account under, double balance)
    : Account(under.Id(), under.Name(), under.Pesel()),
    balance(balance) {

}

double AccountWithBalance::Balance() const {
    return balance;
}
