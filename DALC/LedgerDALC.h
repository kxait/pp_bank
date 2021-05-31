#ifndef PP_BANK_LEDGERDALC_H
#define PP_BANK_LEDGERDALC_H


#include <vector>
#include "../Transaction.h"
#include "../Ledger.h"

class LedgerDALC {
public:
    virtual std::vector<Transaction> getTransactions() = 0;
    virtual Ledger* getLedger() = 0;
    virtual bool saveTransactions(std::vector<Transaction> transactions) = 0;
};


#endif //PP_BANK_LEDGERDALC_H
