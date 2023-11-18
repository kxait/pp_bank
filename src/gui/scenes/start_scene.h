#ifndef PP_BANK_STARTSCENE_H
#define PP_BANK_STARTSCENE_H

#include "../../bank_manager.h"
#include "../lib/scene_composer.h"
#include "../lib/component.h"
#include "../lib/scene.h"

class start_scene : public scene {
    bank_manager* m_man;
    bool m_config_found = false;
public:
    start_scene(bank_manager*, scene_composer*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_STARTSCENE_H
