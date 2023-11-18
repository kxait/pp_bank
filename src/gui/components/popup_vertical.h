#ifndef PP_BANK_POPUPVERTICAL_H
#define PP_BANK_POPUPVERTICAL_H


#include "..\lib"
#include "paged_list.h"

class popup_vertical : public paged_list {
    std::vector<std::string> m_options;
    int m_menu_result = -1;
public:
    popup_vertical(int, int, int, int, const std::vector<std::string>&, component* = nullptr);
    static popup_vertical produce(std::vector<std::string>);
    static long get_result(const std::vector<std::string>&);
    long act();
    void render() override;
    void emit_parent(std::string a, long b) override;
};


#endif //PP_BANK_POPUPVERTICAL_H
