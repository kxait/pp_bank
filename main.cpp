#include <iostream>
#include "AccountList.h"
#include "BankManager.h"
#include "Data/AccountMock.h"
#include "Data/LedgerMock.h"

int main() {
    auto ledg = dynamic_cast<LedgerDALC*>(new LedgerMock());
    auto acc = dynamic_cast<AccountDALC*>(new AccountMock());

    auto manager = new BankManager(ledg, acc);

    try {
        manager->createTransaction(1, 2, 575757575757);
    }catch(const std::invalid_argument& e) {
        std::cout << "COS SIE ZEPSULO!!!:" << std::endl;
        std::cout << e.what() << std::endl;
    }

    auto a = manager->getAccountList();
    for(auto i : a) {
        std::cout << i.Id() << ", " << i.Name() << ", " << i.Pesel() << ", " << i.Balance() << std::endl;
    }

    manager->saveData();
    return 0;
}
