#ifndef PP_BANK_INPUTFIELD_H
#define PP_BANK_INPUTFIELD_H


#include "../Lib/Component.h"

class InputField : public Component {
    std::string value{};

public:
    InputField(int, int, int, int, EventObserver*, std::string = "");
    void handleInput(int) override;
    void render() override;
    std::string getValue();
    void setValue(std::string);
};


#endif //PP_BANK_INPUTFIELD_H
