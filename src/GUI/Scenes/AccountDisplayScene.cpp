#include "AccountDisplayScene.h"
#include "../Components/PagedList.h"
#include "../Components/BankAccountDisplay.h"
#include "../../Log/UserLogger.h"
#include"../Components/Popup.h"
#include "../Components/PopupVertical.h"
#include "../Lib/ScreenProps.h"
#include "../Components/NewTransactionDialog.h"
#include "../Components/SingleValueDialog.h"
#include "../Components/EditAccountDialog.h"

AccountDisplayScene::AccountDisplayScene(SceneComposer* comp, BankManager * mgr)
    : Scene(comp),
    man(mgr){

}

long AccountDisplayScene::act() {
    createComponents();

    render();

    int c;
    auto focusedComponent = components[focusedIndex];
    while((c = focusedComponent->getInput()) != 0 && !end) {
        if(c == 9) {
            rotateFocusedIndex();
            components[focusedIndex]->render();
        }else{
            focusedComponent->handleInput(c);
        }
        focusedComponent->render();
        focusedComponent = components[focusedIndex];
        if(end) break;
    }

    return 0;
}

static bool confirm(std::string a) {
    auto result = Popup::getResult(PopupType::OkCancel, a);
    return !result;
}

void AccountDisplayScene::emit(std::string a, long b) {
    //auto logger = UserLogger::getLogger();
    if(a == "list_choice") {
        components[1]->emit("bank_account_choice", b+1); // pominiecie okienka
        components[1]->render();
    }else if(a == "list_choice_enter") {
        Popup::getResult(PopupType::Ok, accounts[b+1].Name());
        render();
    }else if(a == "bank_account_display_action") {
        components[focusedIndex]->removeFocus();
        auto result = PopupVertical::getResult({
            "Modyfikuj",
            "Usun z wyplata",
            "Usun z przelewem",
            "Nowa transakcja"
        });

        switch(result) {
            case 0: { // modyfikuj
                auto result = *(man->getAccount(b));
                try {
                    result = EditAccountDialog::getResult(result.Name(), result.Pesel(), "Modyfikuj konto");
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja")) {
                        Popup::getResult(PopupType::Ok, e.what());
                    }
                    break;
                }
                try {
                    man->modifyAccount(b, result.Name(), result.Pesel(), result.Deleted());
                } catch (const std::exception &e) {
                    Popup::getResult(PopupType::Ok, UserLogger::getString({
                        "nie udalo sie zmodifykowac konta: ",
                        e.what()
                    }));
                }
                createComponents();
                break;
            }
            case 1: { // usun z wyplata
                if(confirm("Usunac konto?")) {
                    try {
                        man->deleteAccountWithPayout(b);
                    } catch (const std::exception &e) {
                        Popup::getResult(PopupType::Ok, e.what());
                        break;
                    }
                    Popup::getResult(PopupType::Ok, "Usunieto konto");
                    createComponents();
                }
                break;
            }
            case 2: { // usun z przelewem
                std::string result{};
                try {
                    result = SingleValueDialog::getResult("Id konta docelowego", "0");
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja")) {
                        Popup::getResult(PopupType::Ok, e.what());
                    }
                    break;
                }

                if(!confirm("Usunac konto?")) {
                    break;
                }

                try {
                    auto resultParsed = std::stol(result);
                    man->deleteAccountWithTransfer(b, resultParsed);
                } catch (const std::exception &e) {
                    Popup::getResult(PopupType::Ok, UserLogger::getString({
                        "nie udalo sie usunac konta: ",
                        e.what()
                    }));
                }

                createComponents();
                break;
            }
            case 3: { // nowa transakcja
                Transaction result{0, 0, 0, 0};
                try {
                    result = NewTransactionDialog::getResult(std::to_string(b));
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja")) {
                        Popup::getResult(PopupType::Ok, e.what());
                    }
                    break;
                }
                try {
                    man->createTransaction(result.SourceId(), result.DestId(), result.Amount());
                } catch (const std::exception &e) {
                    Popup::getResult(PopupType::Ok, UserLogger::getString({
                          "nie udalo sie stworzyc tranzakcji: ",
                          e.what()
                    }));
                }
                createComponents();
                break;
            }
        }
        components[focusedIndex]->focus();
        render();
    }else if(a == "choice") { // wybor opcji z paska na dole
        switch(b) {
            case 0: { // nowe konto
                Account result{0, "", "", false};
                try {
                    result = EditAccountDialog::getResult("", "", "Nowe konto");
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja")) {
                        Popup::getResult(PopupType::Ok, e.what());
                    }
                    break;
                }
                try {
                    man->createAccount(result.Name(), result.Pesel(), result.Deleted());
                } catch (const std::exception &e) {
                    Popup::getResult(PopupType::Ok, UserLogger::getString({
                        "nie udalo sie stworzyc konta: ",
                        e.what()
                    }));
                }
                createComponents();
                break;
            }
            case 1: { // powrot
                composerParent->switchScene("SceneMenu");
                end = true;
                break;
            }
        }
        render();
    }
}

void AccountDisplayScene::render() {
    refresh();
    for(auto i : components) {
        i->render();
    }
}

void AccountDisplayScene::rotateFocusedIndex() {
    components[focusedIndex]->removeFocus();
    focusedIndex++;
    if(focusedIndex >= components.size()) {
        focusedIndex = 0;
    }
    components[focusedIndex]->focus();
}

void AccountDisplayScene::createComponents() {
    end = false;
    std::vector<std::string> names;
    accounts = man->getAccountListSkipDeleted();
    for(auto i : accounts) {
        if(i.Id() == 0 || i.Deleted()) {
            continue;
        }
        auto name = UserLogger::getString({std::to_string(i.Id()), ": ", i.Name()});
        names.push_back(name);
    }

    auto props = ScreenProps::get();

    //for(auto i : components) {
        //delete i;
        // bledy ktore sie pojawily przez delete:
        // - pure virtual function called!
        // - segmentation fault
        // przez brak delete prawdopodobnie jest (niewielki) wyciek pamieci
        // nie wiemy dlaczego to sie tu pojawia
    //}

    auto bottomBarOptions = std::vector<std::string>{
        "Nowe konto",
        "Powrot"
    };

    components = std::vector<Component*>({
             dynamic_cast<Component*>(new PagedList(0, 0, props.Height()-1, props.Width()/2, names, this)),
             dynamic_cast<Component*>(new BankAccountDisplay(0, props.Width()/2+1, props.Height()-1, props.Width()/2-1, accounts, this)),
             dynamic_cast<Component*>(MenuHorizontal::produce(
                     props.Height()-1,
                     0,
                     bottomBarOptions,
                     reinterpret_cast<Component *>(this)))
     });

    components[1]->emit("bank_account_choice", 1); // zaczniecie od pierwszego konta procz okienka
    components[focusedIndex]->focus();
}
