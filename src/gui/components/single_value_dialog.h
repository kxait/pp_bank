#ifndef PP_BANK_SINGLEVALUEDIALOG_H
#define PP_BANK_SINGLEVALUEDIALOG_H

#include "..\lib"
#include <vector>
#include<string>

class single_value_dialog : public component {
    std::vector<component*> m_fields;
    int m_focused_field = 0;
    void rotate_focused_field(bool = true);
    char m_end = 0;
    std::string m_title;
public:
    single_value_dialog(int, int, int, int, event_observer*, std::string = "Podaj wartosc", std::string = "");
    std::string get_data() const;
    void emit(std::string, long) override;
    void handle_input(int) override;
    void render() override;
    void set_field_value(const std::string&) const;
    static single_value_dialog produce(const std::string& = "", const std::string& = "");
    static std::string get_result(const std::string& = "", const std::string& = "");
    long act();
};


#endif //PP_BANK_SINGLEVALUEDIALOG_H
