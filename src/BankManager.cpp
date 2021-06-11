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

AccountList::Account* BankManager::createAccount(std::string holderName, std::string holderPesel, bool deleted) {
    return modifyAccount(accList->getNextAccountId(), std::move(holderName), std::move(holderPesel), deleted);
}

AccountList::Account* BankManager::modifyAccount(long id, std::string holderName, std::string holderPesel, bool deleted) {
    auto acc = new AccountList::Account(id, std::move(holderName), std::move(holderPesel), deleted);
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

    if(transAcc != 0) {
        createTransaction(acc->Id(), destId, ledger->getBalance(id));
    }
    accList->deleteAccount(id);
}

// rzuci wyjatek jesli transakcja jest niepoprawna
Ledger::Transaction BankManager::createTransaction(long sourceId, long destId, double amount) {
    auto accountsExist =
        accList->accountExists(sourceId)
        && accList->accountExists(destId);
    auto sourceAccDeletedOrDestAccDeleted = accountsExist &&
        (accList->getAccount(sourceId)->Deleted()
        || accList->getAccount(destId)->Deleted());
    if(accList->accountExists(sourceId)
        && accList->accountExists(destId)
        && amount != 0
        && !sourceAccDeletedOrDestAccDeleted
        && accountsExist) {
        auto trans = transFac.createTransaction(sourceId, destId, amount);
        return trans;
    }
    throw std::runtime_error("nie udalo sie stworzyc transakcji z zlymi danymi");
}

void BankManager::saveData() {
    throwIfLedgerInvalid();

    auto a = const_cast<std::vector<Ledger::Transaction>*>(ledger->getTransactions());
    ledgDalc->saveTransactions(*a);

    auto b = const_cast<std::vector<AccountList::Account>*>(accList->getAccounts());
    accDalc->saveAccounts(*b);
}

void BankManager::readData() {
    AccountList* newAccountList;
    try {
        newAccountList = accDalc->getAccountList();
    }catch(const std::exception& e) {
        throw std::runtime_error("nie udalo sie przeczytac listy kont");
    }

    auto oldAccountList = accList;
    accList = newAccountList;

    Ledger* newLedger;
    try {
        newLedger = ledgDalc->getLedger();
    }catch(const std::exception& e) {
        accList = oldAccountList;
        throw std::runtime_error("nie udalo sie przeczytac listy transakcji");
    }
    if(!newLedger->isLedgerValid()) {
        accList = oldAccountList;
        throw std::runtime_error("nowa lista transakcji byla niepoprawna");
    }

    if(ledger != nullptr) {
        delete ledger;
    }
    ledger = newLedger;
    transFac = TransactionFactory(ledger);

    if(oldAccountList != nullptr) {
        delete oldAccountList;
    }
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

std::vector<AccountWithBalance> BankManager::getAccountListSkipDeleted() {
    auto accs = accList->getAccounts();
    std::vector<AccountWithBalance> accsBalances{};
    for(auto acc : *accs) {
        if(acc.Deleted()) {
            continue;
        }
        auto bal = ledger->getBalance(acc.Id());
        AccountWithBalance a(acc, bal);
        accsBalances.push_back(a);
    }
    return accsBalances;
}

void BankManager::throwIfLedgerInvalid() {
    if(!ledger->isLedgerValid()) {
        throw std::runtime_error("lista transakcji byla niepoprawna podczas sprawdzenia");
    }
}

std::vector<Transaction> BankManager::getTransactions() {
    auto transactions = *ledger->getTransactions();
    return transactions;
}

std::string BankManager::getAccountsDbLocation() {
    return accDalc->getLocation();
}

std::string BankManager::getLedgerDbLocation() {
    return ledgDalc->getLocation();
}
