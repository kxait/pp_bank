#ifndef PP_BANK_EDITACCOUNTDIALOG_H
#define PP_BANK_EDITACCOUNTDIALOG_H

#include "../lib/component.h"
#include "../../account_list.h"
#include<vector>

class edit_account_dialog : public component {
    std::vector<component*> m_fields;
    int m_focused_field = 0;
    void rotate_focused_field(bool = true);
    char m_end = 0;
    std::string m_title;
public:
    edit_account_dialog(int, int, int, int, event_observer*, const std::string& = "", const std::string& = "", std::string = "Konto");
    account get_data() const;
    void emit(std::string, long) override;
    void handle_input(int) override;
    void render() override;
    void set_field_value(int, const std::string&) const;
    static edit_account_dialog produce(std::string = "", std::string = "", std::string = "Konto");
    static account get_result(const std::string& = "", const std::string& = "", const std::string& = "Konto");
    long act();
};


#endif //PP_BANK_EDITACCOUNTDIALOG_H


