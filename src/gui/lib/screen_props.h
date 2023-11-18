#ifndef PP_BANK_SCREENPROPS_H
#define PP_BANK_SCREENPROPS_H

#include<ncurses.h>


class screen_props {
    int m_width, m_height;
    screen_props(int, int);
public:
    int width() const;
    int height() const;
    static screen_props get(const WINDOW* win = stdscr);
};


#endif //PP_BANK_SCREENPROPS_H
