#ifndef PP_BANK_POPUPVERTICAL_H
#define PP_BANK_POPUPVERTICAL_H


#include "../Lib/Component.h"
#include "PagedList.h"
#include<iostream>

class PopupVertical : public PagedList {
    std::vector<std::string> options;
    int menuResult = -1;
public:
    PopupVertical(int, int, int, int, std::vector<std::string>, Component* = nullptr);
    static PopupVertical produce(std::vector<std::string>);
    static long getResult(std::vector<std::string>);
    long act();
    void render() override;
    void emitParent(std::string a, long b) override;
};


#endif //PP_BANK_POPUPVERTICAL_H
