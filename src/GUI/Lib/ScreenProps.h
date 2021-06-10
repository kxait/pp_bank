#ifndef PP_BANK_SCREENPROPS_H
#define PP_BANK_SCREENPROPS_H

#include<ncurses.h>


class ScreenProps {
    int width, height;
    ScreenProps(int, int);
public:
    int Width() const;
    int Height() const;
    static ScreenProps get(WINDOW* win = stdscr);
};


#endif //PP_BANK_SCREENPROPS_H
