#ifndef PP_BANK_BANKACCOUNTDISPLAY_H
#define PP_BANK_BANKACCOUNTDISPLAY_H


#include "../Lib/Component.h"
#include "../../AccountWithBalance.h"

class BankAccountDisplay : public Component {
    std::vector<AccountWithBalance> accounts;
    int currentAccount = -1;
    const static int minWidth = 14;
    const static int minHeight = 6;
public:
    BankAccountDisplay(int, int, int, int, std::vector<AccountWithBalance>, EventObserver* = nullptr);
    void emit(std::string, long) override;
    void handleInput(int) override;
    void render() override;
};


#endif //PP_BANK_BANKACCOUNTDISPLAY_H
