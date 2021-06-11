#include "SceneMenuScene.h"
#include "../Components/PagedList.h"
#include "../Lib/ScreenProps.h"
#include "../Components/Popup.h"
#include "../../Log/UserLogger.h"

void SceneMenuScene::render() {
    mvprintw(0, 0, "--- BANK ---");
    mvprintw(1, 0, "Ustawienia: (config.csv)");
    mvprintw(2, 0, UserLogger::getString({
        "Baza kont: ",
        man->getAccountsDbLocation()
    }).data());
    mvprintw(3, 0, UserLogger::getString({
         "Baza transakcji: ",
         man->getLedgerDbLocation()
    }).data());
    refresh();

    for(auto i : components) {
        i->render();
    }
}

void SceneMenuScene::createComponents() {
    end = false;
    auto props = ScreenProps::get();

    components = std::vector<Component*>({
        dynamic_cast<Component*>(new PagedList(4, 1, props.Height() - 4, props.Width() - 2, {
            UserLogger::getString({
                "Konta (",
                std::to_string(man->getAccountListSkipDeleted().size()-1),
                ")"
            }),
            UserLogger::getString({
                "Transakcje (",
                std::to_string(man->getTransactions().size()),
                ")"
            }),
            "Zapisz dane",
            "Zczytaj dane",
            "Informacje o projekcie",
            "Wyjdz",
        }, this))
    });

    components[0]->focus();
}

SceneMenuScene::SceneMenuScene(BankManager* mgr, SceneComposer * par)
    : Scene(par),
    man(mgr) {

}

long SceneMenuScene::act() {
    createComponents();
    render();

    int c;
    while((c = components[focusedIndex]->getInput()) != 0 && !end) {
        components[focusedIndex]->handleInput(c);
        render();
        if(end) break;
    }

    return 0;
}

static bool confirm(std::string t) {
    return !Popup::getResult(PopupType::OkCancel, t);
}

void SceneMenuScene::emit(std::string a, long b) {
    if(a == "list_choice_enter") {
        switch(b) {
            case 0: { // konta
                composerParent->switchScene("AccountDisplay");
                end = true;
                break;
            }
            case 1: { // transakcje
                composerParent->switchScene("TransactionList");
                end = true;
                break;
            }

            case 2: { // zapisz dane
                if(confirm("Zapisac dane?")) {
                    try {
                        man->saveData();
                    } catch (const std::exception &e) {
                        Popup::getResult(PopupType::Ok, e.what());
                        break;
                    }
                    Popup::getResult(PopupType::Ok, "Udalo sie zapisac dane");
                    render();
                }
                break;
            }
            case 3: { // czytaj
                if(confirm("Zczytac dane? Usunie to wszystkie zmiany.")) {
                    try {
                        man->readData();
                        createComponents();
                    } catch (const std::exception &e) {
                        Popup::getResult(PopupType::Ok, e.what());
                        break;
                    }
                    Popup::getResult(PopupType::Ok, "Udalo sie wczytac dane");
                    render();
                }
                break;
            }
            case 4: { // info
                Popup::getResult(PopupType::Ok, std::vector<std::string>{
                        "Projekt banku na zajecia z podstaw programowania",
                        "Autorzy:",
                        "- Tomasz Osika",
                        "- Kacper Kuriata",
                        "- Olaf Nowak",
                        "- Dominik Rempuszewski",
                        "Uzyto biblioteki ncurses"
                });
                break;
            }
            case 5: { // wyjdz
                composerParent->exit(0);
                end = true;
                break;
            }
        }
    }
}
