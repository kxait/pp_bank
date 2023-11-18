#include "ledger_csv.h"

LedgerCsv::LedgerCsv(std::string filename, char separator)
    :filename(std::move(filename)),
    separator(separator) {

}

std::vector<Transaction> LedgerCsv::getTransactions() {
    auto result = std::vector<Transaction>{};
    CsvReader input(filename, separator);
    input.scan();
    // sourceId destId amount
    while(!input.isEof()) {
        auto sourceId = input.getField<long>();
        auto destId = input.getField<long>();
        auto amount = input.getField<double>();
        Transaction a(0, sourceId, destId, amount);
        result.push_back(a);
    }
    return result;
}

Ledger *LedgerCsv::getLedger() {
    auto result = new Ledger();
    for(auto i : getTransactions()) {
        result->addTransaction(i);
    }
    return result;
}

bool LedgerCsv::saveTransactions(std::vector<Transaction> transactions) {
    CsvWriter output(filename, separator);
    for(auto i : transactions) {
        output.pushField(std::to_string(i.SourceId()));
        output.pushField(std::to_string(i.DestId()));
        output.pushField(std::to_string(i.Amount()));
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

std::string LedgerCsv::getLocation() {
    return filename;
}
