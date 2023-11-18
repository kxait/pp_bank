#include "edit_account_dialog.h"

#include "new_transaction_dialog.h"
#include "input_field.h"
#include "../lib/screen_props.h"
#include "menu_horizontal.h"
#include "../../log/user_logger.h"

void edit_account_dialog::rotate_focused_field(const bool down) {
    m_fields[m_focused_field]->remove_focus();
    if(down) {
        m_focused_field++;
    }else{
        m_focused_field--;
    }
    if(m_focused_field == m_fields.size()) {
        m_focused_field = 0;
    }
    if(m_focused_field < 0) {
        m_focused_field = m_fields.size() - 1;
    }
    m_fields[m_focused_field]->focus();
}

edit_account_dialog::edit_account_dialog(const int y, const int x, const int h, const int w, event_observer * par, const std::string&name, const std::string&pesel, std::string title)
    : component(y,x,h,w,par),
    m_title(std::move(title)) {
    keypad(m_win, true);
    m_fields = {
            dynamic_cast<component*>(new input_field(y+2, x+1, 1, m_width-2, this, name)),
            dynamic_cast<component*>(new input_field(y+4, x+1, 1, m_width-2, this, pesel)),
            dynamic_cast<component*>(menu_horizontal::produce(y+m_height-2, x+1, {
                    "Ok",
                    "Anuluj"
            }, this))
    };
    m_fields[m_focused_field]->focus();
}

account edit_account_dialog::get_data() const {
    std::string name, pesel;
    double am;
    try {
        name = dynamic_cast<input_field*>(m_fields[0])->get_value();
        pesel = dynamic_cast<input_field*>(m_fields[1])->get_value();
    }catch(const std::exception& e) {
        const auto logger = user_logger::get_logger();
        logger->log_error(user_logger::get_string({
            "nie udalo sie stworzyc konta z formatki (imienazwisko: ",
            dynamic_cast<input_field*>(m_fields[0])->get_value(),
            ", pesel: ",
            dynamic_cast<input_field*>(m_fields[1])->get_value(),
            ")",
        }));
        throw e;
    }

    return {0, name, pesel, false};
}

void edit_account_dialog::emit(const std::string a, const long b) {
    if(a == "choice") {
        switch(b) {
            case 0: { // ok
                m_end = 1;
                break;
            }
            case 1: { // anuluj
                m_end = 2;
                break;
            }
        }
    }
}

void edit_account_dialog::handle_input(const int a) {
    if(a == KEY_DOWN) {
        rotate_focused_field();
    }else if(a == KEY_UP) {
        rotate_focused_field(false);
    }else{
        m_fields[m_focused_field]->handle_input(a);
    }
}

void edit_account_dialog::render() {
    mvwprintw(m_win, 0, 1, m_title.data());
    mvwprintw(m_win, 1, 1, "Nazwa konta");
    mvwprintw(m_win, 3, 1, "PESEL posiadacza konta");
    wrefresh(m_win);
    for(auto i : m_fields) {
        i->render();
    }
}

void edit_account_dialog::set_field_value(const int a, const std::string&b) const {
    if(a < 2 && a >= 0) {
        dynamic_cast<input_field*>(m_fields[a])->set_value(b);
    }
}

edit_account_dialog edit_account_dialog::produce(std::string name, std::string pesel, std::string title) {
    auto props = screen_props::get();
    return {1, 1, props.height()-2, props.width()-2, nullptr, name, pesel, title};
}

account edit_account_dialog::get_result(const std::string&name, const std::string&pesel, const std::string&title) {
    auto p = produce(name, pesel, title);
    const auto result = p.act();
    if(result == 1) {
        return p.get_data();
    }
    throw std::runtime_error("dialog zakonczyl sie anulacja");
}

long edit_account_dialog::act() {
    int c;
    render();
    while((c = get_input()) != 0 && !m_end) {
        handle_input(c);
        render();
        if(m_end) break; // z jakiegos powodu warunek '!end' nie byl lapany na linii 109, wiec musimy tutaj sprawdzic czy sie nie zakonczylo
    }
    return m_end;
}