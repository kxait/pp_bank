#include "bank_account_display.h"
#include "..\..\log\user_logger.h"

bank_account_display::bank_account_display(const int y, const int x, const int height, const int width, const std::vector<account_with_balance>&list, event_observer* parent)
    : component(y, x, height, width, parent),
    m_accounts(list) {

}

void bank_account_display::emit(const std::string a, const long b) {
    if(a == "bank_account_choice") {
        m_current_account = b;
    }
}

static std::string curl(std::string a, const int width) {
    if(a.size() > width) {
        a = a.substr(0, width - 1);
        a.push_back('&');
    }
    return a;
}

void bank_account_display::render() {
    // ID:
    // Imie:
    // PESEL:
    // Saldo:
    //
    // Modyfikuj Usun
    auto cur_account = m_accounts[m_current_account];

    const int max_width = m_width - 2;

    erase();

    std::string output{};
    output = curl(user_logger::get_string({"ID: ", std::to_string(cur_account.id())}), max_width);
    mvwprintw(m_win, 1, 1, output.data());

    output = curl(user_logger::get_string({"Imie: ", cur_account.name()}), max_width);
    mvwprintw(m_win, 2, 1, output.data());

    output = curl(user_logger::get_string({"Pesel: ", cur_account.pesel()}), max_width);
    mvwprintw(m_win, 3, 1, output.data());

    output = curl(user_logger::get_string({"Saldo: ", std::to_string(cur_account.balance())}), max_width);
    mvwprintw(m_win, 4, 1, output.data());

    // nie ma tu menu, jest tylko jedna akcja, ktora otwiera menu
    output = curl("Akcje", max_width);
    if(m_is_focused) {
        wattron(m_win, A_STANDOUT);
    }
    mvwprintw(m_win, 6, 1, output.data());
    if(m_is_focused) {
        wattroff(m_win, A_STANDOUT);
    }

    wrefresh(m_win);
}

void bank_account_display::handle_input(int i) {
    switch(i) {
        case 10: {
            emit_parent("bank_account_display_action", m_accounts[m_current_account].id());
            break;
        } // enter
    }
}
