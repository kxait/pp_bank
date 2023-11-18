#include "single_value_dialog.h"

#include "input_field.h"
#include "menu_horizontal.h"
#include "..\lib"

void single_value_dialog::rotate_focused_field(const bool down) {
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

single_value_dialog::single_value_dialog(int y, int x, int h, int w, event_observer * par, std::string title, std::string start_value)
    : component(y, x, h, w, par),
      m_title(std::move(title)) {
    keypad(m_win, true);
    m_fields = {
        dynamic_cast<component*>(new input_field(y+2, x+1, 1, m_width-2, this, std::move(start_value))),
        dynamic_cast<component*>(menu_horizontal::produce(y+m_height-2, x+1, {
            "Ok",
            "Anuluj"
        }, this))
    };

    m_fields[0]->focus();
}

std::string single_value_dialog::get_data() const {
    return dynamic_cast<input_field*>(m_fields[0])->get_value();
}

void single_value_dialog::emit(std::string a, long b) {
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

void single_value_dialog::handle_input(int a) {
    if(a == KEY_DOWN) {
        rotate_focused_field();
    }else if(a == KEY_UP) {
        rotate_focused_field(false);
    }else{
        m_fields[m_focused_field]->handle_input(a);
    }
}

void single_value_dialog::render() {
    mvwprintw(m_win, 0, 0, m_title.data());
    wrefresh(m_win);
    for(const auto i : m_fields) {
        i->render();
    }
}

void single_value_dialog::set_field_value(const std::string&a) const {
    dynamic_cast<input_field*>(m_fields[0])->set_value(a);
}

single_value_dialog single_value_dialog::produce(const std::string&title, const std::string&startValue) {
    const auto props = screen_props::get();

    // min 15
    const auto w = (title.size() > 15 ? title.size() : 15);
    constexpr auto h = 6;
    const auto pos_y = props.height() / 2 - h / 2;
    const auto pos_x = props.width() / 2 - w / 2;
    return single_value_dialog(pos_y, pos_x, h, w, nullptr, title, startValue);
}

std::string single_value_dialog::get_result(const std::string&title, const std::string&startValue) {
    auto p = produce(title, startValue);
    const auto result = p.act();
    if(result == 1) {
        return p.get_data();
    }
    throw std::runtime_error("dialog zakonczyl sie anulacja");
}

long single_value_dialog::act() {
    int c;
    render();
    while((c = get_input()) != 0 && !m_end) {
        handle_input(c);
        render();
        if(m_end) break; // z jakiegos powodu warunek '!end' nie byl lapany na linii 109, wiec musimy tutaj sprawdzic czy sie nie zakonczylo
    }
    return m_end;
}
