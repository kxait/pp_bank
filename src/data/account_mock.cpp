#include "account_mock.h"

std::vector<account> account_mock::m_data = {
        account(0, std::string("OKIENKO"), std::string("0"), false),
        account(1, std::string("student"), std::string("12345678911"), false),
        account(2, std::string("drugi student"), std::string("11987654321"), false),
        account(3, std::string("inny student"), std::string("019283746511"), false),
        account(4, std::string("pracownik"), std::string("657483920111"), true),
};;

std::vector<account> account_mock::get_accounts() {
    return m_data;
}

bool account_mock::save_accounts(std::vector<account> save_data) {
    m_data = std::vector<account>(save_data);
    return true;
}

account_list* account_mock::get_account_list() {
    const auto list = new account_list();
    for(auto i : m_data) {
        list->add_or_modify_account(i);
    }
    return list;
}

std::string account_mock::get_location() {
    return "mock";
}
