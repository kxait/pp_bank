#ifndef PP_BANK_POPUP_H
#define PP_BANK_POPUP_H

#include "../Lib/Component.h"
#include "MenuHorizontal.h"
#include<iostream>

enum PopupType {
    Ok,
    OkCancel
};

class Popup : public Component {
    PopupType type;
    std::vector<std::string> message;
    MenuHorizontal* mh;
    long menuResult = -1;
public:
    Popup(int, int, int, int, PopupType, std::vector<std::string>, Component* = nullptr);
    static Popup produce(PopupType, std::string);
    static Popup produce(PopupType, std::vector<std::string>);
    static Popup* producePtr(PopupType, std::vector<std::string>);
    static long getResult(PopupType, std::string);
    static long getResult(PopupType, std::vector<std::string>);
    long act();
    void emit(std::string, long) override;
    void handleInput(int) override;
    void render() override;
    ~Popup();
};


#endif //PP_BANK_POPUP_H
