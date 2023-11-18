#include "popup.h"
#include "../Lib/ScreenProps.h"
#include "..\..\Log\user_logger.h"

#include<sstream>
#include<map>

Popup::Popup(int y, int x, int height, int width, PopupType type, std::vector<std::string> message, Component* parent)
    :Component(y, x, height, width, parent),
    type(type),
    message(std::move(message)){

    std::map<PopupType, std::vector<std::string>> options{
            {PopupType::Ok, {"Ok"}},
            {PopupType::OkCancel, {"Ok", "Anuluj"}},
    };
    long w = MenuHorizontal::getWidth(options[type]);
    mh = new MenuHorizontal(y+height-2, x+2, 1, w, options[type], this);
}

Popup Popup::produce(PopupType type, std::string message) {
    return produce(type, std::vector<std::string>{message});
}

long Popup::getResult(PopupType type, std::string message) {
    auto p = produce(type, message);
    return p.act();
}

void Popup::handleInput(int i) {
    mh->handleInput(i);
}

void Popup::render() {
    //mvwprintw(win, 2, 2, message.data());
    int idx = 0;
    for(auto i : message) {
        if(i.size() > width-2) {
            i = i.substr(0, width-5);
            i.push_back('&');
        }
        mvwprintw(win, 2+(idx++), 2, i.data());
    }
    wrefresh(win);
    removeFocus();
    mh->focus();
    mh->render();
}

Popup::~Popup() {
    delete mh;
}

void Popup::emit(std::string a, long b) {
    if(a == "choice") {
        menuResult = b;
        emitParent("choice", b);
        //delete this;
    }
}

// zabierz kontrole
long Popup::act() {
    render();
    keypad(win, true);
    int c;
    while((c = wgetch(win))) {
        handleInput(c);
        if(menuResult != -1) {
            return menuResult;
        }
    }
}

Popup Popup::produce(PopupType type, std::vector<std::string> strings) {
    auto props = ScreenProps::get();
    auto maxWidth = props.Width() - 4;
    auto maxHeight = props.Height() - 4;
    auto len = 0;
    for(auto i : strings) {
        if(i.size() > maxWidth) {
            len = maxWidth;
        }
        if(i.size() > len) {
            len = i.size();
        }
    }

    auto h = 1 + strings.size() + 5;
    auto w = (len / maxWidth >= 1) ? maxWidth + 4 : len + 4;
    w = (w < 14) ? 14 : w;

    auto posY = props.Height() / 2 - h / 2;
    auto posX = props.Width() / 2 - w / 2;

    return {(int)posY, (int)posX, (int)h, (int)w, type, strings};
}

long Popup::getResult(PopupType type, std::vector<std::string> message) {
    auto p = produce(type, message);
    return p.act();
}

Popup* Popup::producePtr(PopupType type, std::vector<std::string> strings) {
    auto props = ScreenProps::get();
    auto maxWidth = props.Width() - 4;
    auto maxHeight = props.Height() - 4;
    auto len = 0;
    for(auto i : strings) {
        if(i.size() > maxWidth) {
            len = maxWidth;
        }
        if(i.size() > len) {
            len = i.size();
        }
    }

    auto h = 1 + strings.size() + 5;
    auto w = (len / maxWidth >= 1) ? maxWidth + 4 : len + 4;
    w = (w < 14) ? 14 : w;

    auto posY = props.Height() / 2 - h / 2;
    auto posX = props.Width() / 2 - w / 2;

    return new Popup((int)posY, (int)posX, (int)h, (int)w, type, strings);
}
