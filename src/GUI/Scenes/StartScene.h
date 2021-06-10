#ifndef PP_BANK_STARTSCENE_H
#define PP_BANK_STARTSCENE_H

#include "../../BankManager.h"
#include <vector>
#include "../Lib/SceneComposer.h"
#include "../Lib/Scene.h"
#include "../Lib/Component.h"

class StartScene : public Scene {
    BankManager* man;
    bool configFound = false;
public:
    StartScene(BankManager*, SceneComposer*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_STARTSCENE_H
