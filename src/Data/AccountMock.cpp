#include "AccountMock.h"

std::vector<Account> AccountMock::data = {
        Account(0, std::string("OKIENKO"), std::string("0")),
        Account(1, std::string("student"), std::string("12345678911")),
        Account(2, std::string("drugi student"), std::string("11987654321")),
        Account(3, std::string("inny student"), std::string("019283746511")),
        Account(4, std::string("pracownik"), std::string("657483920111")),
};;

std::vector<Account> AccountMock::getAccounts() {
    return data;
}

bool AccountMock::saveAccounts(std::vector<Account> saveData) {
    data = std::vector<Account>(saveData);
    return true;
}

AccountList* AccountMock::getAccountList() {
    auto list = new AccountList();
    for(auto i : data) {
        list->addOrModifyAccount(i);
    }
    return list;
}

std::string AccountMock::getLocation() {
    return "mock";
}
