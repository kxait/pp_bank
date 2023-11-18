#ifndef PP_BANK_COMPONENT_H
#define PP_BANK_COMPONENT_H

#include<ncurses.h>
#include "event_observer.h"


class component : public event_observer {
protected:
    int m_x, m_y, m_width, m_height;
    WINDOW* m_win;
    static constexpr int m_min_width = 0, m_min_height = 0;
    bool m_is_focused = false;
public:
    component(int, int, int, int, event_observer* = nullptr);
    virtual ~component();
    virtual void focus();
    virtual void remove_focus();
    virtual void handle_input(int) = 0;
    virtual void render() = 0;
    int get_input();
    void erase();
};


#endif //PP_BANK_COMPONENT_H
