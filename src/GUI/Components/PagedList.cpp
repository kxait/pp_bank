#include "PagedList.h"
#include "../../Log/UserLogger.h"

PagedList::PagedList(int y, int x, int height, int width, std::vector<std::string> data, EventObserver* parent)
    : Component( y, x, height, width, parent),
    data(data){
    keypad(win, true);
}

void PagedList::handleInput(int i) {
    switch(i) {
        case KEY_UP: {
            selectedIndex--;
            if(selectedIndex < 0) {
                selectedIndex = data.size() - 1;
            }
            emitParent("list_choice", selectedIndex);
            break;
        }
        case KEY_DOWN: {
            selectedIndex++;
            if(selectedIndex >= data.size()) {
                selectedIndex = 0;
            }
            emitParent("list_choice", selectedIndex);
            break;
        }
        case 10: {
            emitParent("list_choice_enter", selectedIndex);
            break;
        }
    }
}

void PagedList::render() {
    int maxListItems = height - 2;
    int maxEntryWidth = width - 2;
    int page = selectedIndex / maxListItems;
    int currentPageStart = page * maxListItems;
    int maxIndex = page * maxListItems + (maxListItems);
    maxIndex = (maxIndex > data.size() ? (int)data.size() : maxIndex);

    //std::cout << "maxListItems: " << maxListItems << " page: " << page << " currentPageStart: " << currentPageStart << " maxIndex: " << maxIndex << std::endl;

    erase();

    for(int i = currentPageStart; i < maxIndex; i++) {
        int currentListY = i - currentPageStart;
        if(selectedIndex == i && isFocused) {
            wattron(win, A_STANDOUT);
        }
        mvwprintw(win, 1 + currentListY, 1, data[i].substr(0, maxEntryWidth).data());
        if(selectedIndex == i && isFocused) {
            wattroff(win, A_STANDOUT);
        }
    }

    int maxPages = data.size() / (maxListItems + 1) + 1;
    mvwprintw(win, height - 1, 1, UserLogger::getString({std::to_string(page + 1), "/", std::to_string(maxPages)}).data());
    wrefresh(win);
}
