#include "BankManagerGui.h"
#include "Lib/ScreenProps.h"
#include "Components/Popup.h"
#include "../Log/UserLogger.h"
#include "Components/PagedList.h"
#include "Components/BankAccountDisplay.h"
#include "Scenes/AccountDisplayScene.h"
#include "Scenes/TransactionListScene.h"
#include "Scenes/SceneMenuScene.h"
#include "Lib/SceneComposer.h"
#include "Scenes/StartScene.h"
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
