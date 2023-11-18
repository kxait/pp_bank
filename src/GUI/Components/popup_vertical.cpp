#include "popup_vertical.h"
#include "../Lib/ScreenProps.h"

PopupVertical::PopupVertical(int y, int x, int h, int w, std::vector<std::string> opts, Component * par)
    : PagedList(y, x, h, w, opts, par) {
}

PopupVertical PopupVertical::produce(std::vector<std::string> a) {
    int w = 0;
    for(auto i : a) {
        if(i.size() > w) {
            w = i.size();
        }
    }
    int h = a.size() + 2;

    auto props = ScreenProps::get();
    auto posY = props.Height() / 2 - h / 2;
    auto posX = props.Width() / 2 - w / 2;

    return {posY, posX, h, w + 2, a};
}

long PopupVertical::getResult(std::vector<std::string> a) {
    auto p = produce(a);
    p.focus();
    return p.act();
}

long PopupVertical::act() {
    render();
    keypad(win, true);
    int c;
    while((c = wgetch(win))) {
        handleInput(c);
        if(menuResult != -1) {
            return menuResult;
        }
        render();
    }

    return 0;
}

void PopupVertical::emitParent(std::string a, long b) {
    if(a == "list_choice") {
        return;
    }
    if(a == "list_choice_enter") {
        EventObserver::emitParent("vertical_popup_choice", b);
        menuResult = b;
        return;
    }
    EventObserver::emitParent(a, b);
}

void PopupVertical::render() {
    PagedList::render();
    mvwprintw(win, 0, 1, "Akcja");
    wrefresh(win);
}
