#ifndef PP_BANK_MENUHORIZONTAL_H
#define PP_BANK_MENUHORIZONTAL_H

#include "../Lib/Component.h"
#include<vector>
#include<iostream>

class MenuHorizontal : public Component {
    std::vector<std::string> options;
    int highlighted = 0;
    int result = -1;
    int startIdx;

public:
    MenuHorizontal(int, int, int, int, std::vector<std::string>, Component*, int = 0);
    void handleInput(int) override;
    void render() override;
    static MenuHorizontal* produce(int, int, std::vector<std::string>, Component*);
    static long getWidth(std::vector<std::string>);
};


#endif //PP_BANK_MENUHORIZONTAL_H
