#include<iostream>
#include"Ledger.h"
#include"AccountList.h"

int main() {
    auto acc = new AccountList();
    auto ledg = new Ledger();
    acc->addOrModifyAccount(Account(1, "student", "12344"));
    ledg->addTransaction(Transaction(0, 0, 1, 10.0));

    auto trans = ledg->getTransaction(0);

    std::cout << trans->SourceId() << ", " << trans->DestId() << ", " << trans->Amount() << std::endl;
}