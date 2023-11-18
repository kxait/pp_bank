#include "account_csv.h"

AccountCsv::AccountCsv(std::string filename, char separator)
    : filename(std::move(filename)),
    separator(separator) {

}

std::vector<AccountList::Account> AccountCsv::getAccounts() {
    auto result = std::vector<AccountList::Account>{};
    CsvReader input(filename, separator);
    input.scan();
    // id name pesel
    while(!input.isEof()) {
        auto id = input.getField<long>();
        auto name = input.getField<std::string>();
        auto pesel = input.getField<std::string>();
        auto deleted = input.getField<bool>();
        AccountList::Account a(id, name, pesel, deleted);
        result.push_back(a);
    }
    return result;
}

AccountList *AccountCsv::getAccountList() {
    auto result = new AccountList();
    for(auto i : getAccounts()) {
        result->addOrModifyAccount(i);
    }
    return result;
}

bool AccountCsv::saveAccounts(std::vector<AccountList::Account> set) {
    CsvWriter output(filename, separator);
    for(auto i : set) {
        output.pushField(std::to_string(i.Id()));
        output.pushField(i.Name());
        output.pushField(i.Pesel());
        output.pushField(i.Deleted() ? "1" : "0");
        output.eol();
    }

    try {
        output.eof();
    }
    catch(const std::exception&) {
        return false;
    }

    return true;
}

std::string AccountCsv::getLocation() {
    return filename;
}
