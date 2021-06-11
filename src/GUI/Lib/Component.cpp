#include "Component.h"
#include<iostream>

Component::Component(int y, int x, int height, int width, EventObserver* parent)
    : y(y),
    x(x),
    height(height),
    width(width),
    EventObserver(parent) {
    if(height < minHeight || width < minWidth) {
        throw std::out_of_range("za male okno");
    }
    win = newwin(height, width, y, x);
    erase();
}

Component::~Component() {
    delwin(win);
}

void Component::focus() {
    isFocused = true;
}

void Component::removeFocus() {
    isFocused = false;
}

int Component::getInput() {
    int c;
    c = wgetch(win);
    return c;
}

void Component::erase() {
    werase(win);
    box(win, 0, 0);
}
