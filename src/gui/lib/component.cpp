#include "component.h"
#include<iostream>

component::component(int y, int x, int height, int width, event_observer* parent)
    : m_y(y),
    m_x(x),
    m_height(height),
    m_width(width),
    event_observer(parent) {
    if(height < m_min_height || width < m_min_width) {
        throw std::out_of_range("za male okno");
    }
    m_win = newwin(height, width, y, x);
    erase();
}

component::~component() {
    delwin(m_win);
}

void component::focus() {
    m_is_focused = true;
}

void component::remove_focus() {
    m_is_focused = false;
}

int component::get_input() {
    const int c = wgetch(m_win);
    return c;
}

void component::erase() {
    werase(m_win);
    box(m_win, 0, 0);
}
