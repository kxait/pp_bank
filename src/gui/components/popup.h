#ifndef PP_BANK_POPUP_H
#define PP_BANK_POPUP_H

#include "../lib/component.h"
#include "menu_horizontal.h"

enum popup_type_t {
    Ok,
    OkCancel
};

class popup : public component {
    popup_type_t m_type;
    std::vector<std::string> m_message;
    menu_horizontal* m_mh;
    long m_menu_result = -1;
public:
    popup(int, int, int, int, popup_type_t, std::vector<std::string>, component* = nullptr);
    static popup produce(popup_type_t, const std::string&);
    static popup produce(popup_type_t, std::vector<std::string>);
    static popup* produce_ref(popup_type_t, const std::vector<std::string>&);
    static long get_result(popup_type_t, const std::string&);
    static long get_result(popup_type_t, const std::vector<std::string>&);
    long act();
    void emit(std::string, long) override;
    void handle_input(int) override;
    void render() override;
    ~popup();
};


#endif //PP_BANK_POPUP_H
