#ifndef PP_BANK_NEWTRANSACTIONDIALOG_H
#define PP_BANK_NEWTRANSACTIONDIALOG_H


#include "..\lib"
#include "../../ledger.h"
#include<vector>

class new_transaction_dialog : public component {
    std::vector<component*> m_fields;
    int m_focused_field = 0;
    void rotate_focused_field(bool = true);
    char m_end = 0;
public:
    new_transaction_dialog(int, int, int, int, event_observer*, const std::string& = "", const std::string& = "");
    transaction get_data() const;
    void emit(std::string, long) override;
    void handle_input(int) override;
    void render() override;
    void set_field_value(int, const std::string&) const;
    static new_transaction_dialog produce(std::string = "", std::string = "");
    static transaction get_result(const std::string& = "", const std::string& = "");
    long act();
};


#endif //PP_BANK_NEWTRANSACTIONDIALOG_H
