#ifndef PP_BANK_BANKMANAGERGUI_H
#define PP_BANK_BANKMANAGERGUI_H


#include "..\bank_manager.h"

class BankManagerGui {
    BankManager* man;
public:
    BankManagerGui(BankManager* mgr);
    void MakeMenu();
};


#endif //PP_BANK_BANKMANAGERGUI_H
