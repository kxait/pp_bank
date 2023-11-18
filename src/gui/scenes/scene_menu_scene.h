#ifndef PP_BANK_SCENEMENUSCENE_H
#define PP_BANK_SCENEMENUSCENE_H


#include "../lib/scene.h"
#include "../../bank_manager.h"

class scene_menu_scene : public scene  {
    bank_manager* m_manager;
    std::vector<component*> m_components;
    void render() const;
    void create_components();
    int m_focused_index = 0;
public:
    scene_menu_scene(bank_manager*, scene_composer*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_SCENEMENUSCENE_H
