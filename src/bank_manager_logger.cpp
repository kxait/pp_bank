#include "bank_manager_logger.h"
#include <sstream>

bank_manager_logger::bank_manager_logger(ledger_dalc *ledg_dalc, account_dalc *acc_dalc, user_logger* logger)
    : bank_manager(ledg_dalc, acc_dalc),
    m_logger(logger) {
    logger->log_info("stworzono nowy bank manager");
}

account_list::account *bank_manager_logger::create_account(const std::string holder_name, const std::string holder_pesel, const bool deleted) {
    auto a = bank_manager::create_account(holder_name, holder_pesel, deleted);
    std::stringstream ss{};
    ss << "stworzono konto id " << a->id() << " nazwa '" << holder_name << "' pesel '" << holder_pesel << "' " << " usuniety: " << deleted;
    m_logger->log_info(ss.str());
    return a;
}

account_list::account *bank_manager_logger::modify_account(const long id, const std::string holder_name, const std::string holder_pesel, const bool deleted) {
    auto a = bank_manager::modify_account(id, holder_name, holder_pesel, deleted);
    std::stringstream ss{};
    ss << "zmodyfikowano konto id " << a->id() << " nowa nazwa '" << holder_name << "' nowy pesel '" << holder_pesel << "' " << " usuniety: " << deleted;
    m_logger->log_info(ss.str());
    return a;
}

void bank_manager_logger::delete_account_with_payout(const long id) {
    std::stringstream ss{};
    try {
        bank_manager::delete_account_with_payout(id);
    }catch(const std::exception& e) {
        ss << "nie udalo sie usunac konta id " << id << ": " << e.what();
        m_logger->log_error(ss.str());
        throw e;
    }
    ss << "usunieto konto " << id;
    m_logger->log_info(ss.str());
}

void bank_manager_logger::delete_account_with_transfer(const long id, const long dest_id) {
    std::stringstream ss{};
    try {
        bank_manager::delete_account_with_transfer(id, dest_id);
    }catch(const std::exception& e) {
        ss << "nie udalo sie usunac konta id " << id << ": " << e.what();
        m_logger->log_error(ss.str());
        throw e;
    }
    ss << "usunieto konto " << id << " z transferem do konta " << dest_id;
    m_logger->log_info(ss.str());
}

ledger::transaction bank_manager_logger::create_transaction(const long source_id, const long dest_id, const double amount) {
    std::stringstream ss{};
    try {
        const auto a = bank_manager::create_transaction(source_id, dest_id, amount);
        ss << "stworzono transakcje " << a.id() << " o parametrach id zrodlowe: " << source_id << " id docelowe: " << dest_id << " ilosc: " << amount;
        m_logger->log_info(ss.str());
        return a;
    }catch(const std::exception& e) {
        ss << "nie udalo sie stworzyc transakcji o parametrach: id zrodlowe: " << source_id
            << " id docelowe: " << dest_id
            << " ilosc: " << amount
            << ": " << e.what();
        m_logger->log_error(ss.str());
        throw e;
    }
}

void bank_manager_logger::save_data() {
    std::stringstream ss{};
    try {
        bank_manager::save_data();
    }catch(const std::exception& e) {
        ss << "nie udalo sie zapisac danych: " << e.what();
        m_logger->log_error(ss.str());
        throw e;
    }
    ss << "udalo sie zapisac dane";
    m_logger->log_info(ss.str());
}

void bank_manager_logger::read_data() {
    std::stringstream ss{};
    try {
        bank_manager::read_data();
    }catch(const std::exception& e) {
        ss << "nie udalo sie przeczytac nowych danych: " << e.what();
        m_logger->log_error(ss.str());
        throw e;
    }
    ss << "udalo sie przeczytac nowe dane";
    m_logger->log_info(ss.str());
}

std::vector<account_with_balance> bank_manager_logger::get_account_list() {
    return bank_manager::get_account_list();
}

double bank_manager_logger::account_balance(const long id) {
    return bank_manager::account_balance(id);
}

account_list::account *bank_manager_logger::get_account(const long id) {
    return bank_manager::get_account(id);
}
