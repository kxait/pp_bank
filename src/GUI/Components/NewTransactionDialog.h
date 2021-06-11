#ifndef PP_BANK_NEWTRANSACTIONDIALOG_H
#define PP_BANK_NEWTRANSACTIONDIALOG_H


#include "../Lib/Component.h"
#include "../../Ledger.h"
#include<vector>

class NewTransactionDialog : public Component {
    std::vector<Component*> fields;
    int focusedField = 0;
    void rotateFocusedField(bool = true);
    char end = 0;
public:
    NewTransactionDialog(int, int, int, int, EventObserver*, std::string = "", std::string = "");
    Transaction getData();
    void emit(std::string, long) override;
    void handleInput(int) override;
    void render() override;
    void setFieldValue(int, std::string);
    static NewTransactionDialog produce(std::string = "", std::string = "");
    static Transaction getResult(std::string = "", std::string = "");
    long act();
};


#endif //PP_BANK_NEWTRANSACTIONDIALOG_H
