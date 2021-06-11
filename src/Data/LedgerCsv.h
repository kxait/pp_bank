#ifndef PP_BANK_LEDGERCSV_H
#define PP_BANK_LEDGERCSV_H

#include <vector>
#include "../DALC/LedgerDALC.h"
#include "CsvReaderWriter.h"

class LedgerCsv : public LedgerDALC {
    std::string filename;
    char separator;
public:
    LedgerCsv(std::string filename, char separator = ';');
    std::vector<Ledger::Transaction> getTransactions() override;
    Ledger* getLedger() override;
    bool saveTransactions(std::vector<Ledger::Transaction> transactions) override;
    std::string getLocation() override;
};


#endif //PP_BANK_LEDGERCSV_H
