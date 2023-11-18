#include "bank_manager_gui.h"
#include "scenes\account_display_scene.h"
#include "scenes\transaction_list_scene.h"
#include "scenes\scene_menu_scene.h"
#include "lib\scene_composer.h"
#include "scenes\start_scene.h"
#include<ncurses.h>
#include<sstream>

bank_manager_gui::bank_manager_gui(bank_manager *mgr)
    : m_manager(mgr) {

}

void bank_manager_gui::make_menu() const {
    WINDOW* win = initscr();
    curs_set(0);
    noecho();
    refresh();

    scene_composer a{};
    a.register_scene("Start", new start_scene(m_manager, &a));
    a.register_scene("SceneMenu", new scene_menu_scene(m_manager, &a));
    a.register_scene("TransactionList", new transaction_list_scene(&a, m_manager));
    a.register_scene("AccountDisplay", new account_display_scene(&a, m_manager));
    a.switch_scene("Start");
    a.run();

    delwin(win);
    resetterm();
}
