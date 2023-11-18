#include "menu_horizontal.h"

#include "..\..\log\user_logger.h"

menu_horizontal::menu_horizontal(int y, int x, int h, int w, std::vector<std::string> opts, component* parent, const int start_idx)
    : component(y,x,h,w,parent),
    m_options(std::move(opts)),
    m_start_index(start_idx){
    keypad(m_win, true);
}

long menu_horizontal::get_width(const std::vector<std::string>&opts) {
    long w = -1;
    for(const auto& i : opts) {
        w += i.size() + 1;
    }
    return w;
}

void menu_horizontal::handle_input(int i) {
    switch(i) {
        case KEY_LEFT: {
            m_highlighted--;
            if(m_highlighted < 0){
                m_highlighted = m_options.size() - 1;
            }
            break;
        }
        case KEY_RIGHT: {
            m_highlighted++;
            if(m_highlighted >= m_options.size()){
                m_highlighted = 0;
            }
            break;
        }
        case 10: { // enter
            m_result = m_highlighted + m_start_index;
            emit_parent("choice", m_result);
        }
        default: {
            break;
        }
    }
    render();
}

void menu_horizontal::render() {
    int w = 0;
    for(int i = 0; i < m_options.size(); i++) {
        auto opt = m_options[i];
        const auto check = (m_highlighted == i && m_is_focused);
        if(check) {
            wattron(m_win, A_STANDOUT);
        }
        mvwaddstr(m_win, 0, w, opt.data());
        if(check) {
            wattroff(m_win, A_STANDOUT);
        }
        w += opt.size();
        if(i+1 != m_options.size()) {
            mvwaddstr(m_win, 0, w, " ");
            w++;
        }
    }
    wrefresh(m_win);
}

menu_horizontal* menu_horizontal::produce(const int y, const int x, const std::vector<std::string>&a, component * par) {
    return new menu_horizontal(y, x, 1, get_width(a), a, par);
}
