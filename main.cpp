#include <iostream>
#include "src\bank_manager_logger.h"
#include "src\Data\account_mock.h"
#include "src\Data\ledger_mock.h"
#include "src\Log\file_logger.h"
#include "src\Log\console_logger.h"
#include "src\Log\user_logger.h"
#include "src\GUI\bank_manager_gui.h"
#include "src\DALC\config_dalc.h"
#include "src\Data\config_mock.h"
#include "src\Data\config_csv.h"
#include "src\Data\ledger_csv.h"
#include "src\Data\account_csv.h"
#include "src\bank_config.h"

int main() {
    auto conf = dynamic_cast<ConfigDALC*>(new ConfigCsv("config.csv"));

    BankConfig* bc;

    try {
        bc = new BankConfig(conf);
    }catch(const std::exception& e) {
        std::cout << "nie udalo sie otworzyc pliku konfiguracyjnego. upewnij sie ze w folderze z plikiem wykonywalnym znajduje sie plik konfiguracyjny config.csv. plik konfiguracyjny jest plikiem csv rozdzielanym znakiem ';'" << std::endl;
        std::cout << "dodatkowe informacje: " << e.what() << std::endl;
        exit(-1);
    }

    auto ledgDbLoc = bc->LedgerDbLocation();
    auto accDbLoc = bc->AccountsDbLocation();

    auto ledg = dynamic_cast<LedgerDALC*>(new LedgerCsv(ledgDbLoc));
    auto acc = dynamic_cast<AccountDALC*>(new AccountCsv(accDbLoc));

    UserLogger l{};

    FileLogger fl{"log.txt"};
    ConsoleLogger cl;

    l.registerLogger(dynamic_cast<Logger*>(&fl));
    //l.registerLogger(dynamic_cast<Logger*>(&cl));

    auto manager = new BankManagerLogger(ledg, acc, &l);

    manager->saveData();

    BankManagerGui a{dynamic_cast<BankManager*>(manager)};
    a.MakeMenu();

    return 0;
}
