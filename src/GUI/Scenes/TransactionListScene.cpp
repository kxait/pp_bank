#include "TransactionListScene.h"
#include "../Components/PagedList.h"
#include "../Components/MenuHorizontal.h"
#include "../Components/NewTransactionDialog.h"
#include "../Components/Popup.h"
#include "../Lib/ScreenProps.h"
#include "../../Log/UserLogger.h"

#include<cstring>

TransactionListScene::TransactionListScene(SceneComposer * comp, BankManager * mgr)
    : Scene(comp),
    man(mgr) {

}

void TransactionListScene::render() {
    erase();
    for(auto i : components) {
        i->render();
    }
}

void TransactionListScene::rotateFocusedIndex() {
    components[focusedIndex]->removeFocus();
    focusedIndex++;
    if(focusedIndex >= components.size()) {
        focusedIndex = 0;
    }
    components[focusedIndex]->focus();
}

void TransactionListScene::createComponents() {
    end = false;
    focusedIndex = 0;
    accounts = man->getAccountList();
    transactions = man->getTransactions();

    // id \t sourceName \t destName \t amount
    auto props = ScreenProps::get();
    int maxWidth = props.Width()-2;
    std::vector<std::string> names;
    for(auto i : transactions) {
        auto sourceName = UserLogger::getString({
            accounts[i.SourceId()].Deleted() ? "(X)" : "",
            accounts[i.SourceId()].Name(),
            "(",
            std::to_string(i.SourceId()),
            ")"
        });
        auto destName = UserLogger::getString({
            accounts[i.DestId()].Deleted() ? "(X)" : "",
            accounts[i.DestId()].Name(),
            "(",
            std::to_string(i.DestId()),
            ")"
        });
        names.push_back(UserLogger::getString({
            std::to_string(i.Id()),
            ": ",
            sourceName,
            " -> ",
            destName,
            ": ",
            std::to_string(i.Amount()),
        }));
    }

    components = std::vector<Component*>{{
        dynamic_cast<Component*>(new PagedList(0, 0, props.Height()-1, props.Width(), names, this)),
        dynamic_cast<Component*>(MenuHorizontal::produce(props.Height()-1, 0, std::vector<std::string>{
            "Nowa transakcja", "Powrot"
        }, reinterpret_cast<Component*>(this)))
    }};

    components[0]->focus();
    render();
}

long TransactionListScene::act() {
    createComponents();

    render();

    int c;
    auto focusedComponent = components[focusedIndex];
    while((c = focusedComponent->getInput()) != 0 && !end) {
        if(c == 9) { // tab
            rotateFocusedIndex();
        }else{
            focusedComponent->handleInput(c);
        }
        focusedComponent = components[focusedIndex];
        render();
        if(end) break;
    }

    return 0;
}

void TransactionListScene::emit(std::string a, long b) {
    if(a == "choice") {
        switch(b) {
            case 0: {
                Transaction result{0, 0, 0, 0};
                try {
                    result = NewTransactionDialog::getResult();
                }catch(const std::exception& e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if(strcmp(e.what(), "dialog zakonczyl sie anulacja")) {
                        Popup::getResult(PopupType::Ok, e.what());
                    }
                    break;
                }
                try {
                    man->createTransaction(result.SourceId(), result.DestId(), result.Amount());
                }catch(const std::exception& e) {
                    Popup::getResult(PopupType::Ok, UserLogger::getString({
                        "nie udalo sie stworzyc tranzakcji: ",
                        e.what()
                    }));
                }
                createComponents();
                break;
            }
            case 1: {
                composerParent->switchScene("SceneMenu");
                end = true;
                break;
            }
        }
        render();
    }
}
