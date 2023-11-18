#include "scene_composer.h"

#include "..\..\log\user_logger.h"
#include "scene.h"

scene_composer::scene_composer()
{
}

void scene_composer::register_scene(std::string a, scene * b) {
    m_scenes[a] = b;
}

void scene_composer::switch_scene(std::string a) {
    if(m_scenes[a] == nullptr) {
        return;
    }
    m_current_scene = a;
}

void scene_composer::run() {
    m_running = true;
    scene* cur_scene = nullptr;
    while(m_running) {
        erase();
        cur_scene = m_scenes[m_current_scene];
        cur_scene->act();
    }
}

void scene_composer::exit(int a) {
    const auto logger = user_logger::get_logger();
    logger->log_info(user_logger::get_string({
        "aplikacja jest zakonczona z kodem ",
        std::to_string(a)
    }));
    m_running = false;
}
