#include "MenuHorizontal.h"
#include "../../Log/UserLogger.h"

MenuHorizontal::MenuHorizontal(int y, int x, int h, int w, std::vector<std::string> opts, Component* parent, int startIdx)
    : Component(y,x,h,w,parent),
    options(opts),
    startIdx(startIdx){
    keypad(win, true);
}

long MenuHorizontal::getWidth(std::vector<std::string> opts) {
    long w = -1;
    for(auto i : opts) {
        w += i.size() + 1;
    }
    return w;
}

void MenuHorizontal::handleInput(int i) {
    switch(i) {
        case KEY_LEFT: {
            highlighted--;
            if(highlighted < 0){
                highlighted = options.size() - 1;
            }
            break;
        }
        case KEY_RIGHT: {
            highlighted++;
            if(highlighted >= options.size()){
                highlighted = 0;
            }
            break;
        }
        case 10: { // enter
            result = highlighted + startIdx;
            emitParent("choice", result);
        }
        default: {
            break;
        }
    }
    render();
}

void MenuHorizontal::render() {
    int w = 0;
    for(int i = 0; i < options.size(); i++) {
        auto opt = options[i];
        auto check = (highlighted == i && isFocused);
        if(check) {
            wattron(win, A_STANDOUT);
        }
        mvwaddstr(win, 0, w, opt.data());
        if(check) {
            wattroff(win, A_STANDOUT);
        }
        w += opt.size();
        if(i+1 != options.size()) {
            mvwaddstr(win, 0, w, " ");
            w++;
        }
    }
    wrefresh(win);
}

MenuHorizontal* MenuHorizontal::produce(int y, int x, std::vector<std::string> a, Component * par) {
    return new MenuHorizontal(y, x, 1, getWidth(a), a, par);
}
