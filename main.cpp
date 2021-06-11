#include <iostream>
#include "src/BankManagerLogger.h"
#include "src/Data/AccountMock.h"
#include "src/Data/LedgerMock.h"
#include "src/Log/FileLogger.h"
#include "src/Log/ConsoleLogger.h"
#include "src/Log/UserLogger.h"
#include "src/GUI/BankManagerGui.h"
#include "src/DALC/ConfigDALC.h"
#include "src/Data/ConfigMock.h"
#include "src/Data/ConfigCsv.h"
#include "src/Data/LedgerCsv.h"
#include "src/Data/AccountCsv.h"
#include "src/BankConfig.h"

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
