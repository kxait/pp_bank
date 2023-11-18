#include "input_field.h"

#include<sstream>

input_field::input_field(const int y, const int x, const int h, const int w, event_observer * par, std::string start_value)
    : component(y, x, h, w, par){
    keypad(m_win, true); // niestety tu musi byc keypad zeby obslugiwal strzalki
    wclear(m_win);
    m_value = std::move(start_value);
}

void input_field::handle_input(const int a) {
    std::stringstream ss{};
    ss << m_value;
    emit_parent("input_field_input", a);
    if((a >= 'a' && a <= 'z') || (a >= '0' && a <= '9') || a == ' ' || a == '.') {
        ss << static_cast<char>(a);
    }
    if(a == 127) { // backspace
        // https://stackoverflow.com/a/35560422
        m_value = m_value.substr(0, m_value.size() - 1);
        return;
    }
    m_value = ss.str();
}

static std::string curl(std::string a, int w, bool focus) {
    // |abcdefghijk |
    // szer 12 dlug 11 start 0
    // |&cdefghijkl |
    // abcdefghijkl |
    // szer 12 dlug 12 start 2
    // |&defghijklm |
    //abcdefghijklm
    // szer 12 dlug 13 start 3
    // |&efghijklmn |
   //abcdefghijklmn
    // szer 12 dlug 14 start 4
    // poz start przy obcieciu = dlug - szer + 2
    // poz end = koniec
    std::stringstream ss{};

    if(a.size() >= w) {
        ss << "&" << a.substr(a.size() - w + 2, a.size()) << (focus ? '_' : ' ');
    }else{
        ss << a << (focus ? '_' : ' ') << std::string(w-a.size(), ' ');
    }
    return ss.str();
}

void input_field::render() {
    const auto new_value = curl(m_value, m_width-2, m_is_focused);

    wattron(m_win, A_STANDOUT);
    if(m_is_focused) {
        wattron(m_win, A_BOLD);
    }
    wclear(m_win);
    mvwprintw(m_win, 0, 0, new_value.data());
    if(m_is_focused) {
        wattroff(m_win, A_BOLD);
    }
    wattroff(m_win, A_STANDOUT);
    wrefresh(m_win);
}

std::string input_field::get_value() {
    return m_value;
}

void input_field::set_value(std::string a) {
    m_value = std::move(a);
}
