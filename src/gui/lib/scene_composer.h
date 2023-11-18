#ifndef PP_BANK_SCENECOMPOSER_H
#define PP_BANK_SCENECOMPOSER_H

#include<map>
#include "event_observer.h"

class scene;

class scene_composer : public event_observer {
    std::map<std::string, scene*> m_scenes;
    std::string m_current_scene = "none";
    bool m_running = false;
public:
    scene_composer();
    void register_scene(std::string, scene*);
    void switch_scene(std::string);
    void exit(int);
    void run();

};


#endif //PP_BANK_SCENECOMPOSER_H
