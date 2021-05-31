#ifndef PP_BANK_TRANSACTION_H
#define PP_BANK_TRANSACTION_H

class Transaction {
    long id;
    long sourceId;
    long destinationId;
    double amount;
public:
    Transaction(long id, long sourceId, long destinationId, double amount);
    long Id() const;
    long SourceId() const;
    long DestId() const;
    double Amount() const;
};


#endif //PP_BANK_TRANSACTION_H
