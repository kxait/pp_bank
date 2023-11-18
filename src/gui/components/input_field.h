#ifndef PP_BANK_INPUTFIELD_H
#define PP_BANK_INPUTFIELD_H


#include "..\lib"

class input_field : public component {
    std::string m_value{};

public:
    input_field(int, int, int, int, event_observer*, std::string = "");
    void handle_input(int) override;
    void render() override;
    std::string get_value();
    void set_value(std::string);
};


#endif //PP_BANK_INPUTFIELD_H
