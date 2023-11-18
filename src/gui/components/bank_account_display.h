#ifndef PP_BANK_BANKACCOUNTDISPLAY_H
#define PP_BANK_BANKACCOUNTDISPLAY_H


#include "../lib/component.h"
#include "../../account_with_balance.h"

class bank_account_display : public component {
    std::vector<account_with_balance> m_accounts{};
    int m_current_account = -1;
    static constexpr int m_min_width = 14;
    static constexpr int m_min_height = 6;
public:
    bank_account_display(int, int, int, int, const std::vector<account_with_balance>&, event_observer* = nullptr);
    void emit(std::string, long) override;
    void handle_input(int) override;
    void render() override;
};


#endif //PP_BANK_BANKACCOUNTDISPLAY_H
