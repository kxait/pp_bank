#ifndef PP_BANK_LEDGERMOCK_H
#define PP_BANK_LEDGERMOCK_H

#include <vector>
#include "..\dalc\ledger_dalc.h"

class ledger_mock : public ledger_dalc {
    static std::vector<ledger::transaction> m_data;
public:
    std::vector<ledger::transaction> get_transactions() override;
    ledger* get_ledger() override;
    bool save_transactions(std::vector<ledger::transaction> transactions) override;
    std::string get_location() override;
};


#endif //PP_BANK_LEDGERMOCK_H
