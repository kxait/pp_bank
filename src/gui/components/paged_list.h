#ifndef PP_BANK_PAGEDLIST_H
#define PP_BANK_PAGEDLIST_H

#include<iostream>
#include<vector>
#include "../lib/component.h"

class paged_list : public component {
    std::vector<std::string> m_data;
    int m_selected_index = 0;
public:
    paged_list(int, int, int, int, std::vector<std::string>, event_observer* = nullptr);
    void handle_input(int) override;
    void render() override;
};


#endif //PP_BANK_PAGEDLIST_H
