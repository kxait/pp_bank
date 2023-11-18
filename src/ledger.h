#ifndef PP_BANK_LEDGER_H
#define PP_BANK_LEDGER_H

#include <vector>
#include <map>


class ledger {
public:
    class transaction {
        long m_id;
        long m_source_id;
        long m_destination_id;
        double m_amount;
    public:
        transaction(long id, long source_id, long destination_id, double amount);
        long id() const;
        long source_id() const;
        long dest_id() const;
        double amount() const;
    };
    ledger();
    bool add_transaction(const transaction&t);
    long get_transaction_id(long id) const;
    transaction* get_transaction(long id);
    const std::vector<transaction>* get_transactions() const;
    double get_balance(long account_id);
    long get_next_transaction_id() const;
    bool is_ledger_valid();
    long trans_qty() const;
    std::map<long, double> get_balance_sheet() const;
private:
    std::vector<transaction> m_ledger{};

};

typedef ledger::transaction transaction;

#endif //PP_BANK_LEDGER_H
