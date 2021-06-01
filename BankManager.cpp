#include "BankManager.h"

#include <utility>
#include "DALC/LedgerDALC.h"
#include "DALC/AccountDALC.h"

BankManager::BankManager(LedgerDALC* ledgDalc, AccountDALC* accDalc)
    : transFac(nullptr),
    ledgDalc(ledgDalc),
    accDalc(accDalc) {
    readData();
    transFac = TransactionFactory(ledger);
}

AccountList::Account* BankManager::createAccount(std::string holderName, std::string holderPesel) {
    return modifyAccount(accList->getNextAccountId(), std::move(holderName), std::move(holderPesel));
}

AccountList::Account* BankManager::modifyAccount(long id, std::string holderName, std::string holderPesel) {
    auto acc = new AccountList::Account(id, std::move(holderName), std::move(holderPesel));
    accList->addOrModifyAccount(*acc);
    return acc;
}

void BankManager::deleteAccountWithPayout(long id) {
    deleteAccountWithTransfer(id, 0);
}

void BankManager::deleteAccountWithTransfer(long id, long destId) {
    auto transAcc = ledger->getBalance(id);
    auto acc = accList->getAccount(id);
    if(transAcc == -1 || acc == nullptr) {
        throw std::out_of_range("account doesnt exist");
    }

    transFac.createTransaction(acc->Id(), destId, ledger->getBalance(id));
    accList->deleteAccount(id);
}

// rzuci wyjatek jesli transakcja jest niepoprawna
Ledger::Transaction BankManager::createTransaction(long sourceId, long destId, double amount) {
    if(accList->accountExists(sourceId) && accList->accountExists(destId) && amount != 0) {
        auto trans = transFac.createTransaction(sourceId, destId, amount);
        return trans;
    }
    throw std::runtime_error("couldn't create transaction with bad data");
}

void BankManager::saveData() {
    throwIfLedgerInvalid();

    auto a = const_cast<std::vector<Ledger::Transaction>*>(ledger->getTransactions());
    ledgDalc->saveTransactions(*a);

    auto b = const_cast<std::vector<AccountList::Account>*>(accList->getAccounts());
    accDalc->saveAccounts(*b);
}

void BankManager::readData() {
    auto newLedger = ledgDalc->getLedger();
    if(!newLedger->isLedgerValid()) {
        throw std::runtime_error("new ledger was invalid");
    }

    if(ledger != nullptr) {
        delete ledger;
    }
    ledger = newLedger;

    if(accList != nullptr) {
        delete accList;
    }

    accList = accDalc->getAccountList();
}

double BankManager::accountBalance(long id) {
    return ledger->getBalance(id);
}

AccountList::Account *BankManager::getAccount(long id) {
    return accList->getAccount(id);
}

std::vector<AccountWithBalance> BankManager::getAccountList() {
    auto accs = accList->getAccounts();
    std::vector<AccountWithBalance> accsBalances{};
    for(auto acc : *accs) {
        auto bal = ledger->getBalance(acc.Id());
        AccountWithBalance a(acc, bal);
        accsBalances.push_back(a);
    }
    return accsBalances;
}

void BankManager::throwIfLedgerInvalid() {
    if(!ledger->isLedgerValid()) {
        throw std::runtime_error("ledger was invalid during check");
    }
}
