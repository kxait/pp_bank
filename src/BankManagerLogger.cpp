#include "BankManagerLogger.h"
#include <sstream>

BankManagerLogger::BankManagerLogger(LedgerDALC *ledgDalc, AccountDALC *accDalc, UserLogger* logger)
    : BankManager(ledgDalc, accDalc),
    logger(logger) {
    logger->logInfo("stworzono nowy bank manager");
}

AccountList::Account *BankManagerLogger::createAccount(std::string holderName, std::string holderPesel, bool deleted) {
    auto a = BankManager::createAccount(holderName, holderPesel, deleted);
    std::stringstream ss{};
    ss << "stworzono konto id " << a->Id() << " nazwa '" << holderName << "' pesel '" << holderPesel << "' " << " usuniety: " << deleted;
    logger->logInfo(ss.str());
    return a;
}

AccountList::Account *BankManagerLogger::modifyAccount(long id, std::string holderName, std::string holderPesel, bool deleted) {
    auto a = BankManager::modifyAccount(id, holderName, holderPesel, deleted);
    std::stringstream ss{};
    ss << "zmodyfikowano konto id " << a->Id() << " nowa nazwa '" << holderName << "' nowy pesel '" << holderPesel << "' " << " usuniety: " << deleted;
    logger->logInfo(ss.str());
    return a;
}

void BankManagerLogger::deleteAccountWithPayout(long id) {
    std::stringstream ss{};
    try {
        BankManager::deleteAccountWithPayout(id);
    }catch(const std::exception& e) {
        ss << "nie udalo sie usunac konta id " << id << ": " << e.what();
        logger->logError(ss.str());
        throw e;
    }
    ss << "usunieto konto " << id;
    logger->logInfo(ss.str());
}

void BankManagerLogger::deleteAccountWithTransfer(long id, long destId) {
    std::stringstream ss{};
    try {
        BankManager::deleteAccountWithTransfer(id, destId);
    }catch(const std::exception& e) {
        ss << "nie udalo sie usunac konta id " << id << ": " << e.what();
        logger->logError(ss.str());
        throw e;
    }
    ss << "usunieto konto " << id << " z transferem do konta " << destId;
    logger->logInfo(ss.str());
}

Ledger::Transaction BankManagerLogger::createTransaction(long sourceId, long destId, double amount) {
    std::stringstream ss{};
    try {
        auto a = BankManager::createTransaction(sourceId, destId, amount);
        ss << "stworzono transakcje " << a.Id() << " o parametrach id zrodlowe: " << sourceId << " id docelowe: " << destId << " ilosc: " << amount;
        logger->logInfo(ss.str());
        return a;
    }catch(const std::exception& e) {
        ss << "nie udalo sie stworzyc transakcji o parametrach: id zrodlowe: " << sourceId
            << " id docelowe: " << destId
            << " ilosc: " << amount
            << ": " << e.what();
        logger->logError(ss.str());
        throw e;
    }
}

void BankManagerLogger::saveData() {
    std::stringstream ss{};
    try {
        BankManager::saveData();
    }catch(const std::exception& e) {
        ss << "nie udalo sie zapisac danych: " << e.what();
        logger->logError(ss.str());
        throw e;
    }
    ss << "udalo sie zapisac dane";
    logger->logInfo(ss.str());
}

void BankManagerLogger::readData() {
    std::stringstream ss{};
    try {
        BankManager::readData();
    }catch(const std::exception& e) {
        ss << "nie udalo sie przeczytac nowych danych: " << e.what();
        logger->logError(ss.str());
        throw e;
    }
    ss << "udalo sie przeczytac nowe dane";
    logger->logInfo(ss.str());
}

std::vector<AccountWithBalance> BankManagerLogger::getAccountList() {
    return BankManager::getAccountList();
}

double BankManagerLogger::accountBalance(long id) {
    return BankManager::accountBalance(id);
}

AccountList::Account *BankManagerLogger::getAccount(long id) {
    return BankManager::getAccount(id);
}
