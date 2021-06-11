#ifndef PP_BANK_EDITACCOUNTDIALOG_H
#define PP_BANK_EDITACCOUNTDIALOG_H

#include "../Lib/Component.h"
#include "../../AccountList.h"
#include<vector>

class EditAccountDialog : public Component {
    std::vector<Component*> fields;
    int focusedField = 0;
    void rotateFocusedField(bool = true);
    char end = 0;
    std::string title;
public:
    EditAccountDialog(int, int, int, int, EventObserver*, std::string = "", std::string = "", std::string = "Konto");
    Account getData();
    void emit(std::string, long) override;
    void handleInput(int) override;
    void render() override;
    void setFieldValue(int, std::string);
    static EditAccountDialog produce(std::string = "", std::string = "", std::string = "Konto");
    static Account getResult(std::string = "", std::string = "", std::string = "Konto");
    long act();
};


#endif //PP_BANK_EDITACCOUNTDIALOG_H


