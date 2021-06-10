#ifndef PP_BANK_SINGLEVALUEDIALOG_H
#define PP_BANK_SINGLEVALUEDIALOG_H

#include "../Lib/Component.h"
#include <vector>
#include<string>

class SingleValueDialog : public Component {
    std::vector<Component*> fields;
    int focusedField = 0;
    void rotateFocusedField(bool = true);
    char end = 0;
    std::string title;
public:
    SingleValueDialog(int, int, int, int, EventObserver*, std::string = "Podaj wartosc", std::string = "");
    std::string getData();
    void emit(std::string, long) override;
    void handleInput(int) override;
    void render() override;
    void setFieldValue(std::string);
    static SingleValueDialog produce(std::string = "", std::string = "");
    static std::string getResult(std::string = "", std::string = "");
    long act();
};


#endif //PP_BANK_SINGLEVALUEDIALOG_H
