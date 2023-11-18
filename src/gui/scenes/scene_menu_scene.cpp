#include "scene_menu_scene.h"
#include "../components/paged_list.h"
#include "../lib/scene_composer.h"
#include "../lib/screen_props.h"
#include "../components/popup.h"
#include "../../log/user_logger.h"

void scene_menu_scene::render() const {
    mvprintw(0, 0, "--- BANK ---");
    mvprintw(1, 0, "Ustawienia: (config.csv)");
    mvprintw(2, 0, user_logger::get_string({
        "Baza kont: ",
        m_manager->get_accounts_db_location()
    }).data());
    mvprintw(3, 0, user_logger::get_string({
         "Baza transakcji: ",
         m_manager->get_ledger_db_location()
    }).data());
    refresh();

    for(const auto i : m_components) {
        i->render();
    }
}

void scene_menu_scene::create_components() {
    m_end = false;
    const auto props = screen_props::get();

    m_components = std::vector<component*>({
        dynamic_cast<component*>(new paged_list(4, 1, props.height() - 4, props.width() - 2, {
            user_logger::get_string({
                "Konta (",
                std::to_string(m_manager->get_account_list_skip_deleted().size()-1),
                ")"
            }),
            user_logger::get_string({
                "Transakcje (",
                std::to_string(m_manager->get_transactions().size()),
                ")"
            }),
            "Zapisz dane",
            "Zczytaj dane",
            "Informacje o projekcie",
            "Wyjdz",
        }, this))
    });

    m_components[0]->focus();
}

scene_menu_scene::scene_menu_scene(bank_manager* mgr, scene_composer * par)
    : scene(par),
    m_manager(mgr) {

}

long scene_menu_scene::act() {
    create_components();
    render();

    int c;
    while((c = m_components[m_focused_index]->get_input()) != 0 && !m_end) {
        m_components[m_focused_index]->handle_input(c);
        render();
        if(m_end) break;
    }

    return 0;
}

static bool confirm(const std::string&t) {
    return !popup::get_result(OkCancel, t);
}

void scene_menu_scene::emit(const std::string a, const long b) {
    if(a == "list_choice_enter") {
        switch(b) {
            case 0: { // konta
                m_composer_parent->switch_scene("AccountDisplay");
                m_end = true;
                break;
            }
            case 1: { // transakcje
                m_composer_parent->switch_scene("TransactionList");
                m_end = true;
                break;
            }

            case 2: { // zapisz dane
                if(confirm("Zapisac dane?")) {
                    try {
                        m_manager->save_data();
                    } catch (const std::exception &e) {
                        popup::get_result(Ok, e.what());
                        break;
                    }
                    popup::get_result(Ok, "Udalo sie zapisac dane");
                    render();
                }
                break;
            }
            case 3: { // czytaj
                if(confirm("Zczytac dane? Usunie to wszystkie zmiany.")) {
                    try {
                        m_manager->read_data();
                        create_components();
                    } catch (const std::exception &e) {
                        popup::get_result(Ok, e.what());
                        break;
                    }
                    popup::get_result(Ok, "Udalo sie wczytac dane");
                    render();
                }
                break;
            }
            case 4: { // info
                popup::get_result(Ok, std::vector<std::string>{
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
                m_composer_parent->exit(0);
                m_end = true;
                break;
            }
        }
    }
}
