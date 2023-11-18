#ifndef PP_BANK_ACCOUNTDISPLAYSCENE_H
#define PP_BANK_ACCOUNTDISPLAYSCENE_H


#include "..\lib"
#include "..\lib"
#include "..\..\bank_manager.h"

class account_display_scene : public scene {
    bank_manager* m_manager;
    std::vector<account_with_balance> m_accounts;
    std::vector<component*> m_components;
    int m_focused_index = 0;
    void render() const;
    void rotate_focused_index();
    void create_components();
public:
    account_display_scene(scene_composer*, bank_manager*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_ACCOUNTDISPLAYSCENE_H
