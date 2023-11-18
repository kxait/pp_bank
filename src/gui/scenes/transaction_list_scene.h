#ifndef PP_BANK_TRANSACTIONLISTSCENE_H
#define PP_BANK_TRANSACTIONLISTSCENE_H


#include "..\lib"
#include "..\lib"
#include "..\..\bank_manager.h"

class transaction_list_scene : public scene {
    bank_manager* m_manager;
    std::vector<transaction> m_transactions;
    std::vector<account_with_balance> m_accounts;
    std::vector<component*> m_components;
    int m_focused_index = 0;
    void render() const;
    void rotate_focused_index();
    void create_components();
public:
    transaction_list_scene(scene_composer*, bank_manager*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_TRANSACTIONLISTSCENE_H
