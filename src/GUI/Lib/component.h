#ifndef PP_BANK_COMPONENT_H
#define PP_BANK_COMPONENT_H

#include<ncurses.h>
#include<string>
#include<map>
#include "event_observer.h"


class Component : public EventObserver {
protected:
    int x, y, width, height;
    WINDOW* win;
    const static int minWidth = 0, minHeight = 0;
    bool isFocused = false;
public:
    Component(int, int, int, int, EventObserver* = nullptr);
    virtual ~Component();
    virtual void focus();
    virtual void removeFocus();
    virtual void handleInput(int) = 0;
    virtual void render() = 0;
    int getInput();
    void erase();
};


#endif //PP_BANK_COMPONENT_H
