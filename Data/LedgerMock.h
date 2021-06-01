#ifndef PP_BANK_LEDGERMOCK_H
#define PP_BANK_LEDGERMOCK_H


#include <vector>
#include "../Transaction.h"
#include "../DALC/LedgerDALC.h"

class LedgerMock : public LedgerDALC {
    static std::vector<Transaction> data;
public:
    std::vector<Transaction> getTransactions() override;
    Ledger* getLedger() override;
    bool saveTransactions(std::vector<Transaction> transactions) override;
};


#endif //PP_BANK_LEDGERMOCK_H
