#ifndef PP_BANK_LEDGERDALC_H
#define PP_BANK_LEDGERDALC_H

#include <vector>
#include "../Ledger.h"

class LedgerDALC {
public:
    virtual std::vector<Ledger::Transaction> getTransactions() = 0;
    virtual Ledger* getLedger() = 0;
    virtual bool saveTransactions(std::vector<Ledger::Transaction> transactions) = 0;
    virtual std::string getLocation() = 0;
};


#endif //PP_BANK_LEDGERDALC_H
