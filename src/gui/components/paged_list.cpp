#include "paged_list.h"

#include "..\..\log\user_logger.h"

paged_list::paged_list(const int y, const int x, const int height, const int width, std::vector<std::string> data, event_observer* parent)
    : component( y, x, height, width, parent),
    m_data(std::move(data)){
    keypad(m_win, true);
}

void paged_list::handle_input(int i) {
    switch(i) {
        case KEY_UP: {
            m_selected_index--;
            if(m_selected_index < 0) {
                m_selected_index = m_data.size() - 1;
            }
            emit_parent("list_choice", m_selected_index);
            break;
        }
        case KEY_DOWN: {
            m_selected_index++;
            if(m_selected_index >= m_data.size()) {
                m_selected_index = 0;
            }
            emit_parent("list_choice", m_selected_index);
            break;
        }
        case 10: {
            emit_parent("list_choice_enter", m_selected_index);
            break;
        }
    }
}

void paged_list::render() {
    const int max_list_items = m_height - 2;
    const int max_entry_width = m_width - 2;
    const int page = m_selected_index / max_list_items;
    const int current_page_start = page * max_list_items;
    int maxIndex = page * max_list_items + (max_list_items);
    maxIndex = (maxIndex > m_data.size() ? static_cast<int>(m_data.size()) : maxIndex);

    //std::cout << "maxListItems: " << maxListItems << " page: " << page << " currentPageStart: " << currentPageStart << " maxIndex: " << maxIndex << std::endl;

    erase();

    for(int i = current_page_start; i < maxIndex; i++) {
        const int current_list_y = i - current_page_start;
        if(m_selected_index == i && m_is_focused) {
            wattron(m_win, A_STANDOUT);
        }
        mvwprintw(m_win, 1 + current_list_y, 1, m_data[i].substr(0, max_entry_width).data());
        if(m_selected_index == i && m_is_focused) {
            wattroff(m_win, A_STANDOUT);
        }
    }

    const int max_pages = m_data.size() / (max_list_items + 1) + 1;
    mvwprintw(m_win, m_height - 1, 1, user_logger::get_string({std::to_string(page + 1), "/", std::to_string(max_pages)}).data());
    wrefresh(m_win);
}
