#ifndef PP_BANK_PAGEDLIST_H
#define PP_BANK_PAGEDLIST_H

#include<iostream>
#include<vector>
#include "../Lib/Component.h"

class PagedList : public Component {
    std::vector<std::string> data;
    int selectedIndex = 0;
public:
    PagedList(int, int, int, int, std::vector<std::string>, EventObserver* = nullptr);
    void handleInput(int) override;
    void render() override;
};


#endif //PP_BANK_PAGEDLIST_H
