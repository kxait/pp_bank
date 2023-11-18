#ifndef PP_BANK_LEDGERDALC_H
#define PP_BANK_LEDGERDALC_H

#include <vector>
#include "../ledger.h"

class ledger_dalc {
public:
    virtual std::vector<ledger::transaction> get_transactions() = 0;
    virtual ledger* get_ledger() = 0;
    virtual bool save_transactions(std::vector<ledger::transaction> transactions) = 0;
    virtual std::string get_location() = 0;
};


#endif //PP_BANK_LEDGERDALC_H
