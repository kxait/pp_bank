#include "account_display_scene.h"
#include "..\components\paged_list.h"
#include "..\components\bank_account_display.h"
#include "..\..\log\user_logger.h"
#include"../components/popup.h"
#include "..\components\popup_vertical.h"
#include "..\lib"
#include "..\components\new_transaction_dialog.h"
#include "..\components\single_value_dialog.h"
#include "..\components\edit_account_dialog.h"

#include<cstring>

account_display_scene::account_display_scene(scene_composer* comp, bank_manager * mgr)
    : scene(comp),
    m_manager(mgr){

}

long account_display_scene::act() {
    create_components();

    render();

    int c;
    auto focused_component = m_components[m_focused_index];
    while((c = focused_component->get_input()) != 0 && !m_end) {
        if(c == 9) {
            rotate_focused_index();
            m_components[m_focused_index]->render();
        }else{
            focused_component->handle_input(c);
        }
        focused_component->render();
        focused_component = m_components[m_focused_index];
        if(m_end) break;
    }

    return 0;
}

static bool confirm(const std::string&a) {
    const auto result = popup::get_result(OkCancel, a);
    return !result;
}

void account_display_scene::emit(std::string a, long b) {
    //auto logger = UserLogger::getLogger();
    if(a == "list_choice") {
        m_components[1]->emit("bank_account_choice", b+1); // pominiecie okienka
        m_components[1]->render();
    }else if(a == "list_choice_enter") {
        popup::get_result(Ok, m_accounts[b+1].name());
        render();
    }else if(a == "bank_account_display_action") {
        m_components[m_focused_index]->remove_focus();
        auto result = popup_vertical::get_result({
            "Modyfikuj",
            "Usun z wyplata",
            "Usun z przelewem",
            "Nowa transakcja"
        });

        switch(result) {
            case 0: { // modyfikuj
                auto result = *(m_manager->get_account(b));
                try {
                    result = edit_account_dialog::get_result(result.name(), result.pesel(), "Modyfikuj konto");
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja") != 0) {
                        popup::get_result(Ok, e.what());
                    }
                    break;
                }
                try {
                    m_manager->modify_account(b, result.name(), result.pesel(), result.deleted());
                } catch (const std::exception &e) {
                    popup::get_result(Ok, user_logger::get_string({
                                          "nie udalo sie zmodifykowac konta: ",
                                          e.what()
                                      }));
                }
                create_components();
                break;
            }
            case 1: { // usun z wyplata
                if(confirm("Usunac konto?")) {
                    try {
                        m_manager->delete_account_with_payout(b);
                    } catch (const std::exception &e) {
                        popup::get_result(Ok, e.what());
                        break;
                    }
                    popup::get_result(Ok, "Usunieto konto");
                    create_components();
                }
                break;
            }
            case 2: { // usun z przelewem
                std::string result{};
                try {
                    result = single_value_dialog::get_result("Id konta docelowego", "0");
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja") != 0) {
                        popup::get_result(Ok, e.what());
                    }
                    break;
                }

                if(!confirm("Usunac konto?")) {
                    break;
                }

                try {
                    auto resultParsed = std::stol(result);
                    m_manager->delete_account_with_transfer(b, resultParsed);
                } catch (const std::exception &e) {
                    popup::get_result(Ok, user_logger::get_string({
                                          "nie udalo sie usunac konta: ",
                                          e.what()
                                      }));
                }

                create_components();
                break;
            }
            case 3: { // nowa transakcja
                transaction result{0, 0, 0, 0};
                try {
                    result = new_transaction_dialog::get_result(std::to_string(b));
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja") != 0) {
                        popup::get_result(Ok, e.what());
                    }
                    break;
                }
                try {
                    m_manager->create_transaction(result.source_id(), result.dest_id(), result.amount());
                } catch (const std::exception &e) {
                    popup::get_result(Ok, user_logger::get_string({
                                          "nie udalo sie stworzyc tranzakcji: ",
                                          e.what()
                                      }));
                }
                create_components();
                break;
            }
        }
        m_components[m_focused_index]->focus();
        render();
    }else if(a == "choice") { // wybor opcji z paska na dole
        switch(b) {
            case 0: { // nowe konto
                account result{0, "", "", false};
                try {
                    result = edit_account_dialog::get_result("", "", "Nowe konto");
                } catch (const std::exception &e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if (strcmp(e.what(), "dialog zakonczyl sie anulacja") != 0) {
                        popup::get_result(Ok, e.what());
                    }
                    break;
                }
                try {
                    m_manager->create_account(result.name(), result.pesel(), result.deleted());
                } catch (const std::exception &e) {
                    popup::get_result(Ok, user_logger::get_string({
                                          "nie udalo sie stworzyc konta: ",
                                          e.what()
                                      }));
                }
                create_components();
                break;
            }
            case 1: { // powrot
                m_composer_parent->switch_scene("SceneMenu");
                m_end = true;
                break;
            }
        }
        render();
    }
}

void account_display_scene::render() const {
    refresh();
    for(const auto i : m_components) {
        i->render();
    }
}

void account_display_scene::rotate_focused_index() {
    m_components[m_focused_index]->remove_focus();
    m_focused_index++;
    if(m_focused_index >= m_components.size()) {
        m_focused_index = 0;
    }
    m_components[m_focused_index]->focus();
}

void account_display_scene::create_components() {
    m_end = false;
    std::vector<std::string> names;
    m_accounts = m_manager->get_account_list_skip_deleted();
    for(auto i : m_accounts) {
        if(i.id() == 0 || i.deleted()) {
            continue;
        }
        auto name = user_logger::get_string({std::to_string(i.id()), ": ", i.name()});
        names.push_back(name);
    }

    const auto props = screen_props::get();

    //for(auto i : components) {
        //delete i;
        // bledy ktore sie pojawily przez delete:
        // - pure virtual function called!
        // - segmentation fault
        // przez brak delete prawdopodobnie jest (niewielki) wyciek pamieci
        // nie wiemy dlaczego to sie tu pojawia
    //}

    const auto bottom_bar_options = std::vector<std::string>{
        "Nowe konto",
        "Powrot"
    };

    m_components = std::vector<component*>({
             dynamic_cast<component*>(new paged_list(0, 0, props.height()-1, props.width()/2, names, this)),
             dynamic_cast<component*>(new bank_account_display(0, props.width()/2+1, props.height()-1, props.width()/2-1, m_accounts, this)),
             dynamic_cast<component*>(menu_horizontal::produce(
                     props.height()-1,
                     0,
                     bottom_bar_options,
                     reinterpret_cast<component *>(this)))
     });

    m_components[1]->emit("bank_account_choice", 1); // zaczniecie od pierwszego konta procz okienka
    m_components[m_focused_index]->focus();
}
