#ifndef PP_BANK_SCENE_H
#define PP_BANK_SCENE_H

#include<vector>
#include"component.h"

class SceneComposer;

class Scene : public EventObserver {
protected:
    bool end = false;
    SceneComposer* composerParent;
public:
    Scene(SceneComposer*);
    virtual long act() = 0;
    virtual void emit(std::string, long) = 0;

};


#endif //PP_BANK_SCENE_H
