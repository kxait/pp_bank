#ifndef PP_BANK_SCENEMENUSCENE_H
#define PP_BANK_SCENEMENUSCENE_H


#include "..\Lib\scene_composer.h"
#include "../Lib/scene.h"
#include "..\..\bank_manager.h"

class SceneMenuScene : public Scene  {
    BankManager* man;
    std::vector<Component*> components;
    void render();
    void createComponents();
    int focusedIndex = 0;
    void rotateFocusedIndex();
public:
    SceneMenuScene(BankManager*, SceneComposer*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_SCENEMENUSCENE_H
