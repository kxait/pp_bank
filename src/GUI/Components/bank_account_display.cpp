#include "bank_account_display.h"
#include "..\..\Log\user_logger.h"

BankAccountDisplay::BankAccountDisplay(int y, int x, int height, int width, std::vector<AccountWithBalance> list, EventObserver* parent)
    : Component(y, x, height, width, parent),
    accounts(list) {

}

void BankAccountDisplay::emit(std::string a, long b) {
    if(a == "bank_account_choice") {
        currentAccount = b;
    }
}

static std::string curl(std::string a, int width) {
    if(a.size() > width) {
        a = a.substr(0, width - 1);
        a.push_back('&');
    }
    return a;
}

void BankAccountDisplay::render() {
    // ID:
    // Imie:
    // PESEL:
    // Saldo:
    //
    // Modyfikuj Usun
    auto curAccount = accounts[currentAccount];

    int maxWidth = width - 2;

    erase();

    std::string output{};
    output = curl(UserLogger::getString({"ID: ", std::to_string(curAccount.Id())}), maxWidth);
    mvwprintw(win, 1, 1, output.data());

    output = curl(UserLogger::getString({"Imie: ", curAccount.Name()}), maxWidth);
    mvwprintw(win, 2, 1, output.data());

    output = curl(UserLogger::getString({"Pesel: ", curAccount.Pesel()}), maxWidth);
    mvwprintw(win, 3, 1, output.data());

    output = curl(UserLogger::getString({"Saldo: ", std::to_string(curAccount.Balance())}), maxWidth);
    mvwprintw(win, 4, 1, output.data());

    // nie ma tu menu, jest tylko jedna akcja, ktora otwiera menu
    output = curl("Akcje", maxWidth);
    if(isFocused) {
        wattron(win, A_STANDOUT);
    }
    mvwprintw(win, 6, 1, output.data());
    if(isFocused) {
        wattroff(win, A_STANDOUT);
    }

    wrefresh(win);
}

void BankAccountDisplay::handleInput(int i) {
    switch(i) {
        case 10: {
            emitParent("bank_account_display_action", accounts[currentAccount].Id());
            break;
        } // enter
    }
}
