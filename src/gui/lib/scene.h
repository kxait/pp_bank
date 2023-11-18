#ifndef PP_BANK_SCENE_H
#define PP_BANK_SCENE_H

#include<vector>
#include"component.h"

class scene_composer;

class scene : public event_observer {
protected:
    bool m_end = false;
    scene_composer* m_composer_parent;
public:
    explicit scene(scene_composer*);
    virtual long act() = 0;

    void emit(std::string, long) override = 0;

};


#endif //PP_BANK_SCENE_H
