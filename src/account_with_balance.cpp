#include "account_with_balance.h"

AccountWithBalance::AccountWithBalance(AccountList::Account under, double balance)
    : AccountList::Account(under.Id(), under.Name(), under.Pesel(), under.Deleted()),
    balance(balance) {

}

double AccountWithBalance::Balance() const {
    return balance;
}
