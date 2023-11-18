#include "scene_composer.h"

#include <utility>
#include "..\..\Log\user_logger.h"
#include "scene.h"

SceneComposer::SceneComposer()
    : scenes() {
}

void SceneComposer::registerScene(std::string a, Scene * b) {
    scenes[a] = b;
}

void SceneComposer::switchScene(std::string a) {
    if(scenes[a] == nullptr) {
        return;
    }
    currentScene = a;
}

void SceneComposer::run() {
    running = true;
    Scene* curScene = nullptr;
    while(running) {
        erase();
        curScene = scenes[currentScene];
        curScene->act();
    }
}

void SceneComposer::exit(int a) {
    auto logger = UserLogger::getLogger();
    logger->logInfo(UserLogger::getString({
        "aplikacja jest zakonczona z kodem ",
        std::to_string(a)
    }));
    running = false;
}
