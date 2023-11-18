#ifndef PP_BANK_LEDGERCSV_H
#define PP_BANK_LEDGERCSV_H

#include <string>
#include <vector>
#include "..\dalc\ledger_dalc.h"

class ledger_csv : public ledger_dalc {
    std::string m_filename;
    char m_separator;
public:
    explicit ledger_csv(std::string filename, char separator = ';');
    std::vector<ledger::transaction> get_transactions() override;
    ledger* get_ledger() override;
    bool save_transactions(std::vector<ledger::transaction> transactions) override;
    std::string get_location() override;
};


#endif //PP_BANK_LEDGERCSV_H
