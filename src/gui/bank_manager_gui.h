#ifndef PP_BANK_BANKMANAGERGUI_H
#define PP_BANK_BANKMANAGERGUI_H


#include "../bank_manager.h"

class bank_manager_gui {
    bank_manager* m_manager;
public:
    explicit bank_manager_gui(bank_manager* mgr);
    void make_menu() const;
};


#endif //PP_BANK_BANKMANAGERGUI_H
