#include "InputField.h"

#include<sstream>

InputField::InputField(int y, int x, int h, int w, EventObserver * par, std::string startValue)
    : Component(y, x, h, w, par){
    keypad(win, true); // niestety tu musi byc keypad zeby obslugiwal strzalki
    wclear(win);
    value = startValue;
}

void InputField::handleInput(int a) {
    std::stringstream ss{};
    ss << value;
    emitParent("input_field_input", a);
    if((a >= 'a' && a <= 'z') || (a >= '0' && a <= '9') || a == ' ' || a == '.') {
        ss << (char)a;
    }
    if(a == 127) { // backspace
        // https://stackoverflow.com/a/35560422
        value = value.substr(0, value.size() - 1);
        return;
    }
    value = ss.str();
}

static std::string curl(std::string a, int w, bool focus) {
    // |abcdefghijk |
    // szer 12 dlug 11 start 0
    // |&cdefghijkl |
    // abcdefghijkl |
    // szer 12 dlug 12 start 2
    // |&defghijklm |
    //abcdefghijklm
    // szer 12 dlug 13 start 3
    // |&efghijklmn |
   //abcdefghijklmn
    // szer 12 dlug 14 start 4
    // poz start przy obcieciu = dlug - szer + 2
    // poz end = koniec
    std::stringstream ss{};

    if(a.size() >= w) {
        ss << "&" << a.substr(a.size() - w + 2, a.size()) << (focus ? '_' : ' ');
    }else{
        ss << a << (focus ? '_' : ' ') << std::string(w-a.size(), ' ');
    }
    return ss.str();
}

void InputField::render() {
    auto newValue = curl(value, width-2, isFocused);

    wattron(win, A_STANDOUT);
    if(isFocused) {
        wattron(win, A_BOLD);
    }
    wclear(win);
    mvwprintw(win, 0, 0, newValue.data());
    if(isFocused) {
        wattroff(win, A_BOLD);
    }
    wattroff(win, A_STANDOUT);
    wrefresh(win);
}

std::string InputField::getValue() {
    return value;
}

void InputField::setValue(std::string a) {
    value = a;
}
