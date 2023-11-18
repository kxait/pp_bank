#include "transaction_list_scene.h"
#include "../components/paged_list.h"
#include "../components/menu_horizontal.h"
#include "../components/new_transaction_dialog.h"
#include "../components/popup.h"
#include "../lib/scene_composer.h"
#include "../lib/screen_props.h"
#include "../../log/user_logger.h"

#include<cstring>

transaction_list_scene::transaction_list_scene(scene_composer * comp, bank_manager * mgr)
    : scene(comp),
    m_manager(mgr) {

}

void transaction_list_scene::render() const {
    erase();
    for(const auto i : m_components) {
        i->render();
    }
}

void transaction_list_scene::rotate_focused_index() {
    m_components[m_focused_index]->remove_focus();
    m_focused_index++;
    if(m_focused_index >= m_components.size()) {
        m_focused_index = 0;
    }
    m_components[m_focused_index]->focus();
}

void transaction_list_scene::create_components() {
    m_end = false;
    m_focused_index = 0;
    m_accounts = m_manager->get_account_list();
    m_transactions = m_manager->get_transactions();

    // id /t sourceName /t destName /t amount
    const auto props = screen_props::get();
    int max_width = props.width()-2;
    std::vector<std::string> names;
    for(auto i : m_transactions) {
        auto sourceName = user_logger::get_string({
            m_accounts[i.source_id()].deleted() ? "(X)" : "",
            m_accounts[i.source_id()].name(),
            "(",
            std::to_string(i.source_id()),
            ")"
        });
        auto destName = user_logger::get_string({
            m_accounts[i.dest_id()].deleted() ? "(X)" : "",
            m_accounts[i.dest_id()].name(),
            "(",
            std::to_string(i.dest_id()),
            ")"
        });
        names.push_back(user_logger::get_string({
            std::to_string(i.id()),
            ": ",
            sourceName,
            " -> ",
            destName,
            ": ",
            std::to_string(i.amount()),
        }));
    }

    m_components = std::vector<component*>{{
        dynamic_cast<component*>(new paged_list(0, 0, props.height()-1, props.width(), names, this)),
        dynamic_cast<component*>(menu_horizontal::produce(props.height()-1, 0, std::vector<std::string>{
            "Nowa transakcja", "Powrot"
        }, reinterpret_cast<component*>(this)))
    }};

    m_components[0]->focus();
    render();
}

long transaction_list_scene::act() {
    create_components();

    render();

    int c;
    auto focusedComponent = m_components[m_focused_index];
    while((c = focusedComponent->get_input()) != 0 && !m_end) {
        if(c == 9) { // tab
            rotate_focused_index();
        }else{
            focusedComponent->handle_input(c);
        }
        focusedComponent = m_components[m_focused_index];
        render();
        if(m_end) break;
    }

    return 0;
}

void transaction_list_scene::emit(const std::string a, const long b) {
    if(a == "choice") {
        switch(b) {
            case 0: {
                transaction result{0, 0, 0, 0};
                try {
                    result = new_transaction_dialog::get_result();
                }catch(const std::exception& e) {
                    // sprawdzenie czy wyjatek z powodu anulacji, czy cos sie faktycznie wywalilo
                    // nie jest to dobre, ale dziala
                    if(strcmp(e.what(), "dialog zakonczyl sie anulacja") != 0) {
                        popup::get_result(Ok, e.what());
                    }
                    break;
                }
                try {
                    m_manager->create_transaction(result.source_id(), result.dest_id(), result.amount());
                }catch(const std::exception& e) {
                    popup::get_result(Ok, user_logger::get_string({
                                          "nie udalo sie stworzyc tranzakcji: ",
                                          e.what()
                                      }));
                }
                create_components();
                break;
            }
            case 1: {
                m_composer_parent->switch_scene("SceneMenu");
                m_end = true;
                break;
            }
        }
        render();
    }
}
