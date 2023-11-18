#include "bank_manager_gui.h"
#include "Lib/ScreenProps.h"
#include "Components/popup.h"
#include "..\Log\user_logger.h"
#include "Components\paged_list.h"
#include "Components\bank_account_display.h"
#include "Scenes\account_display_scene.h"
#include "Scenes\transaction_list_scene.h"
#include "Scenes\scene_menu_scene.h"
#include "Lib\scene_composer.h"
#include "Scenes\start_scene.h"
#include<ncurses.h>
#include<sstream>

BankManagerGui::BankManagerGui(BankManager *mgr)
    : man(mgr) {

}

void BankManagerGui::MakeMenu() {
    WINDOW* win;
    win = initscr();
    curs_set(0);
    noecho();
    refresh();

    SceneComposer a{};
    a.registerScene("Start", new StartScene(man, &a));
    a.registerScene("SceneMenu", new SceneMenuScene(man, &a));
    a.registerScene("TransactionList", new TransactionListScene(&a, man));
    a.registerScene("AccountDisplay", new AccountDisplayScene(&a, man));
    a.switchScene("Start");
    a.run();

    delwin(win);
    resetterm();
}
