#include "new_transaction_dialog.h"
#include "input_field.h"
#include "..\lib"
#include "menu_horizontal.h"
#include "..\..\log\user_logger.h"

new_transaction_dialog::new_transaction_dialog(
    const int y,
    const int x,
    const int h,
    const int w,
        event_observer * par,
    const std::string&src_value,
    const std::string&dest_value)
    : component(y,x,h,w,par){
    keypad(m_win, true);
    m_fields = {
            dynamic_cast<component*>(new input_field(y+2, x+1, 1, m_width-2, this, src_value)),
            dynamic_cast<component*>(new input_field(y+4, x+1, 1, m_width-2, this, dest_value)),
            dynamic_cast<component*>(new input_field(y+6, x+1, 1, m_width-2, this)),
            dynamic_cast<component*>(menu_horizontal::produce(y+m_height-2, x+1, {
                "Ok",
                "Anuluj"
            }, this))
    };
    m_fields[m_focused_field]->focus();
}

long validate_field_long(input_field* a) {
    const auto val = a->get_value();
    return std::stol(val);
}

double validateFieldFloat(input_field* a) {
    const auto val = a->get_value();
    return std::stod(val);
}

transaction new_transaction_dialog::get_data() const {
    long s_id, d_id;
    double am;
    try {
        s_id = validate_field_long(dynamic_cast<input_field*>(m_fields[0]));
        d_id = validate_field_long(dynamic_cast<input_field*>(m_fields[1]));
        am = validateFieldFloat(dynamic_cast<input_field*>(m_fields[2]));
    }catch(const std::exception& e) {
        const auto logger = user_logger::get_logger();
        logger->log_error(user_logger::get_string({
            "nie udalo sie stworzyc tranzakcji z formatki (sId: ",
            dynamic_cast<input_field*>(m_fields[0])->get_value(),
            ", dId: ",
            dynamic_cast<input_field*>(m_fields[1])->get_value(),
            ", am: ",
            dynamic_cast<input_field*>(m_fields[2])->get_value(),
            ")",
        }));
        throw e;
    }

    return {0, s_id, d_id, am};
}

void new_transaction_dialog::emit(std::string a, long b) {
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

void new_transaction_dialog::handle_input(int a) {
    if(a == KEY_DOWN) {
        rotate_focused_field();
    }else if(a == KEY_UP) {
        rotate_focused_field(false);
    }else{
        m_fields[m_focused_field]->handle_input(a);
    }
}

void new_transaction_dialog::render() {
    mvwprintw(m_win, 0, 1, "Nowa transakcja");
    mvwprintw(m_win, 1, 1, "Id konta zrodlowego");
    mvwprintw(m_win, 3, 1, "Id konta docelowego");
    mvwprintw(m_win, 5, 1, "Wartosc");
    wrefresh(m_win);
    for(const auto i : m_fields) {
        i->render();
    }
}

new_transaction_dialog new_transaction_dialog::produce(std::string src, std::string dst) {
    const auto props = screen_props::get();
    return new_transaction_dialog(1, 1, props.height()-2, props.width()-2, nullptr, src, dst);
}

transaction new_transaction_dialog::get_result(const std::string&src, const std::string&dst) {
    auto p = produce(src, dst);
    const auto result = p.act();
    if(result == 1) {
        return p.get_data();
    }
    throw std::runtime_error("dialog zakonczyl sie anulacja");
}

long new_transaction_dialog::act() {
    int c;
    render();
    while((c = get_input()) != 0 && !m_end) {
        handle_input(c);
        render();
        if(m_end) break; // z jakiegos powodu warunek '!end' nie byl lapany na linii 109, wiec musimy tutaj sprawdzic czy sie nie zakonczylo
    }
    return m_end;
}

void new_transaction_dialog::rotate_focused_field(bool down) {
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

void new_transaction_dialog::set_field_value(const int a, const std::string&b) const {
    if(a < 3 && a >= 0) {
        dynamic_cast<input_field*>(m_fields[a])->set_value(b);
    }
}
