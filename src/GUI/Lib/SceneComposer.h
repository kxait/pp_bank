#ifndef PP_BANK_SCENECOMPOSER_H
#define PP_BANK_SCENECOMPOSER_H

#include<map>
#include "EventObserver.h"

class Scene;

class SceneComposer : public EventObserver {
    std::map<std::string, Scene*> scenes;
    std::string currentScene = "none";
    bool running = false;
public:
    SceneComposer();
    void registerScene(std::string, Scene*);
    void switchScene(std::string);
    void exit(int);
    void run();

};


#endif //PP_BANK_SCENECOMPOSER_H
