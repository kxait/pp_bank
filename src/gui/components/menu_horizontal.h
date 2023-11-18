#ifndef PP_BANK_MENUHORIZONTAL_H
#define PP_BANK_MENUHORIZONTAL_H

#include "..\lib"
#include<vector>
#include<iostream>

class menu_horizontal : public component {
    std::vector<std::string> m_options;
    int m_highlighted = 0;
    int m_result = -1;
    int m_start_index;

public:
    menu_horizontal(int, int, int, int, std::vector<std::string>, component*, int = 0);
    void handle_input(int) override;
    void render() override;
    static menu_horizontal* produce(int, int, const std::vector<std::string>&, component*);
    static long get_width(const std::vector<std::string>&);
};


#endif //PP_BANK_MENUHORIZONTAL_H
