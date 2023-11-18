#include "account_with_balance.h"

account_with_balance::account_with_balance(account under, const double balance)
    : account(under.id(), under.name(), under.pesel(), under.deleted()),
      m_balance(balance) {

}

double account_with_balance::balance() const {
    return m_balance;
}
