#include <iostream>
#include "src/bank_manager_logger.h"
#include "src/log/file_logger.h"
#include "src/log/console_logger.h"
#include "src/log/user_logger.h"
#include "src/gui/bank_manager_gui.h"
#include "src/dalc/config_dalc.h"
#include "src/data/config_csv.h"
#include "src/data/ledger_csv.h"
#include "src/data/account_csv.h"
#include "src/bank_config.h"

int main() {
    auto conf = dynamic_cast<config_dalc*>(new config_csv("config.csv"));

    bank_config* bc;

    try {
        bc = new bank_config(conf);
    }catch(const std::exception& e) {
        std::cout << "nie udalo sie otworzyc pliku konfiguracyjnego. upewnij sie ze w folderze z plikiem wykonywalnym znajduje sie plik konfiguracyjny config.csv. plik konfiguracyjny jest plikiem csv rozdzielanym znakiem ';'" << std::endl;
        std::cout << "dodatkowe informacje: " << e.what() << std::endl;
        exit(-1);
    }

    auto ledg_db_location = bc->ledger_db_location();
    auto acc_db_location = bc->accounts_db_location();

    auto ledg = dynamic_cast<ledger_dalc*>(new ledger_csv(ledg_db_location));
    auto acc = dynamic_cast<account_dalc*>(new account_csv(acc_db_location));

    user_logger l{};

    file_logger fl{"log.txt"};
    console_logger cl;

    l.register_logger(&fl);
    //l.registerLogger(dynamic_cast<Logger*>(&cl));

    auto manager = new bank_manager_logger(ledg, acc, &l);

    manager->save_data();

    bank_manager_gui a{manager};
    a.make_menu();

    return 0;
}
