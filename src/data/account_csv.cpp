#include "account_csv.h"

#include "csv_reader_writer.h"

account_csv::account_csv(std::string filename, const char separator)
    : m_filename(std::move(filename)),
    m_separator(separator) {

}

std::vector<account_list::account> account_csv::get_accounts() {
    auto result = std::vector<account_list::account>{};
    csv_reader input(m_filename, m_separator);
    input.scan();
    // id name pesel
    while(!input.is_eof()) {
        auto id = input.get_field<long>();
        auto name = input.get_field<std::string>();
        auto pesel = input.get_field<std::string>();
        auto deleted = input.get_field<bool>();
        account_list::account a(id, name, pesel, deleted);
        result.push_back(a);
    }
    return result;
}

account_list *account_csv::get_account_list() {
    const auto result = new account_list();
    for(auto i : get_accounts()) {
        result->add_or_modify_account(i);
    }
    return result;
}

bool account_csv::save_accounts(const std::vector<account_list::account> set) {
    csv_writer output(m_filename, m_separator);
    for(auto i : set) {
        output.push_field(std::to_string(i.id()));
        output.push_field(i.name());
        output.push_field(i.pesel());
        output.push_field(i.deleted() ? "1" : "0");
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

std::string account_csv::get_location() {
    return m_filename;
}
