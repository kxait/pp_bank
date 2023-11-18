#include "start_scene.h"
#include "../Lib/ScreenProps.h"
#include "../Components/popup.h"
#include "..\..\Log\user_logger.h"

StartScene::StartScene(BankManager * mgr, SceneComposer * par)
    : Scene(par),
    man(mgr) {

}

long StartScene::act() {
    mvprintw(0, 0, "--- BANK ---");
    refresh();
    Popup::getResult(PopupType::Ok, std::vector<std::string>{
        "Nawigacja:",
        "- zmiana wyboru strzalkami lewo/prawo/gora/dol",
        "- zmiana okna klawiszem tab",
        "- wybor opcji klawiszem enter"
    });
    Popup::getResult(PopupType::Ok, std::vector<std::string>{
        "WAZNE!",
        "",
        "Konto o ID 0 to okienko.",
        "Okienko jest jak okienko w banku - sluzy do wplat i wyplat"
    });
    composerParent->switchScene("SceneMenu");
    return 0;
}

void StartScene::emit(std::string, long) {

}
