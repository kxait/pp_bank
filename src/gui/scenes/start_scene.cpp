#include "start_scene.h"
#include "../components/popup.h"
#include "../../log/user_logger.h"

start_scene::start_scene(bank_manager * mgr, scene_composer * par)
    : scene(par),
    m_man(mgr) {

}

long start_scene::act() {
    mvprintw(0, 0, "--- BANK ---");
    refresh();
    popup::get_result(Ok, std::vector<std::string>{
                          "Nawigacja:",
                          "- zmiana wyboru strzalkami lewo/prawo/gora/dol",
                          "- zmiana okna klawiszem tab",
                          "- wybor opcji klawiszem enter"
                      });
    popup::get_result(Ok, std::vector<std::string>{
                          "WAZNE!",
                          "",
                          "Konto o ID 0 to okienko.",
                          "Okienko jest jak okienko w banku - sluzy do wplat i wyplat"
                      });
    m_composer_parent->switch_scene("SceneMenu");
    return 0;
}

void start_scene::emit(std::string, long) {

}
