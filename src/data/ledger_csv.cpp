#include "ledger_csv.h"

#include <string>

#include "csv_reader_writer.h"

ledger_csv::ledger_csv(std::string filename, const char separator)
    :m_filename(std::move(filename)),
    m_separator(separator) {

}

std::vector<transaction> ledger_csv::get_transactions() {
    auto result = std::vector<transaction>{};
    csv_reader input(m_filename, m_separator);
    input.scan();
    // sourceId destId amount
    while(!input.is_eof()) {
        const auto source_id = input.get_field<long>();
        const auto dest_id = input.get_field<long>();
        const auto amount = input.get_field<double>();
        transaction a(0, source_id, dest_id, amount);
        result.push_back(a);
    }
    return result;
}

ledger *ledger_csv::get_ledger() {
    const auto result = new ledger();
    for(auto i : get_transactions()) {
        result->add_transaction(i);
    }
    return result;
}

bool ledger_csv::save_transactions(const std::vector<transaction> transactions) {
    csv_writer output(m_filename, m_separator);
    for(auto i : transactions) {
        output.push_field(std::to_string(i.source_id()));
        output.push_field(std::to_string(i.dest_id()));
        output.push_field(std::to_string(i.amount()));
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

std::string ledger_csv::get_location() {
    return m_filename;
}
