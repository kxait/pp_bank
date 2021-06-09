#ifndef PP_BANK_LEDGERMOCK_H
#define PP_BANK_LEDGERMOCK_H

#include <vector>
#include "../DALC/LedgerDALC.h"

class LedgerMock : public LedgerDALC {
    static std::vector<Ledger::Transaction> data;
public:
    std::vector<Ledger::Transaction> getTransactions() override;
    Ledger* getLedger() override;
    bool saveTransactions(std::vector<Ledger::Transaction> transactions) override;
    std::string getLocation() override;
};


#endif //PP_BANK_LEDGERMOCK_H
