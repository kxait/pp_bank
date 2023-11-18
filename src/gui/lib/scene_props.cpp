#include "screen_props.h"

screen_props::screen_props(const int y, const int x)
    : m_height(y), m_width(x){

}

int screen_props::width() const {
    return m_width;
}

int screen_props::height() const {
    return m_height;
}

screen_props screen_props::get(const WINDOW *win) {
    int y, x;
    getmaxyx(win, y, x);
    return {y, x};
}
