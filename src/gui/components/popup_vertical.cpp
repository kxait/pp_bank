#include "popup_vertical.h"
#include "..\lib"

popup_vertical::popup_vertical(const int y, const int x, const int h, const int w, const std::vector<std::string>&opts, component * par)
    : paged_list(y, x, h, w, opts, par) {
}

popup_vertical popup_vertical::produce(std::vector<std::string> a) {
    int w = 0;
    for(const auto& i : a) {
        if(i.size() > w) {
            w = i.size();
        }
    }
    int h = a.size() + 2;

    const auto props = screen_props::get();
    auto posY = props.height() / 2 - h / 2;
    auto posX = props.width() / 2 - w / 2;

    return {posY, posX, h, w + 2, a};
}

long popup_vertical::get_result(const std::vector<std::string>&a) {
    auto p = produce(a);
    p.focus();
    return p.act();
}

long popup_vertical::act() {
    render();
    keypad(m_win, true);
    int c;
    while((c = wgetch(m_win))) {
        handle_input(c);
        if(m_menu_result != -1) {
            return m_menu_result;
        }
        render();
    }

    return 0;
}

void popup_vertical::emit_parent(const std::string a, const long b) {
    if(a == "list_choice") {
        return;
    }
    if(a == "list_choice_enter") {
        event_observer::emit_parent("vertical_popup_choice", b);
        m_menu_result = b;
        return;
    }
    event_observer::emit_parent(a, b);
}

void popup_vertical::render() {
    paged_list::render();
    mvwprintw(m_win, 0, 1, "Akcja");
    wrefresh(m_win);
}
