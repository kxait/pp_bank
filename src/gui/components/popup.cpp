#include "popup.h"
#include "..\lib"
#include "..\..\log\user_logger.h"

#include<sstream>
#include<map>

popup::popup(const int y, const int x, const int height, const int width, const popup_type_t type, std::vector<std::string> message, component* parent)
    :component(y, x, height, width, parent),
    m_type(type),
    m_message(std::move(message)){

    std::map<popup_type_t, std::vector<std::string>> options{
            {Ok, {"Ok"}},
            {OkCancel, {"Ok", "Anuluj"}},
    };
    long w = menu_horizontal::get_width(options[type]);
    m_mh = new menu_horizontal(y+height-2, x+2, 1, w, options[type], this);
}

popup popup::produce(const popup_type_t type, const std::string&message) {
    return produce(type, std::vector<std::string>{message});
}

long popup::get_result(const popup_type_t type, const std::string&message) {
    auto p = produce(type, message);
    return p.act();
}

void popup::handle_input(int i) {
    m_mh->handle_input(i);
}

void popup::render() {
    //mvwprintw(win, 2, 2, message.data());
    int idx = 0;
    for(auto i : m_message) {
        if(i.size() > m_width-2) {
            i = i.substr(0, m_width-5);
            i.push_back('&');
        }
        mvwprintw(m_win, 2+(idx++), 2, i.data());
    }
    wrefresh(m_win);
    remove_focus();
    m_mh->focus();
    m_mh->render();
}

popup::~popup() {
    delete m_mh;
}

void popup::emit(std::string a, long b) {
    if(a == "choice") {
        m_menu_result = b;
        emit_parent("choice", b);
        //delete this;
    }
}

// zabierz kontrole
long popup::act() {
    render();
    keypad(m_win, true);
    int c;
    while((c = wgetch(m_win))) {
        handle_input(c);
        if(m_menu_result != -1) {
            return m_menu_result;
        }
    }
    return 0;
}

popup popup::produce(popup_type_t type, std::vector<std::string> strings) {
    const auto props = screen_props::get();
    const auto max_width = props.width() - 4;
    auto max_height = props.height() - 4;
    auto len = 0;
    for(const auto& i : strings) {
        if(i.size() > max_width) {
            len = max_width;
        }
        if(i.size() > len) {
            len = i.size();
        }
    }

    const auto h = 1 + strings.size() + 5;
    auto w = len / max_width >= 1 ? max_width + 4 : len + 4;
    w = w < 14 ? 14 : w;

    const auto pos_y = props.height() / 2 - h / 2;
    const auto pos_x = props.width() / 2 - w / 2;

    return {static_cast<int>(pos_y), static_cast<int>(pos_x), static_cast<int>(h), w, type, strings};
}

long popup::get_result(const popup_type_t type, const std::vector<std::string>&message) {
    auto p = produce(type, message);
    return p.act();
}

popup* popup::produce_ref(const popup_type_t type, const std::vector<std::string>&strings) {
    const auto props = screen_props::get();
    const auto max_width = props.width() - 4;
    auto max_height = props.height() - 4;
    auto len = 0;
    for(const auto& i : strings) {
        if(i.size() > max_width) {
            len = max_width;
        }
        if(i.size() > len) {
            len = i.size();
        }
    }

    const auto h = 1 + strings.size() + 5;
    auto w = (len / max_width >= 1) ? max_width + 4 : len + 4;
    w = (w < 14) ? 14 : w;

    const auto pos_y = props.height() / 2 - h / 2;
    const auto pos_x = props.width() / 2 - w / 2;

    return new popup(static_cast<int>(pos_y), static_cast<int>(pos_x), static_cast<int>(h), w, type, strings);
}
