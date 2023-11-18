#ifndef PP_BANK_STARTSCENE_H
#define PP_BANK_STARTSCENE_H

#include "..\..\bank_manager.h"
#include <vector>
#include "..\Lib\scene_composer.h"
#include "../Lib/scene.h"
#include "../Lib/component.h"

class StartScene : public Scene {
    BankManager* man;
    bool configFound = false;
public:
    StartScene(BankManager*, SceneComposer*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_STARTSCENE_H
