#include "ScreenProps.h"

ScreenProps::ScreenProps(int y, int x)
    : height(y), width(x){

}

int ScreenProps::Width() const {
    return width;
}

int ScreenProps::Height() const {
    return height;
}

ScreenProps ScreenProps::get(WINDOW *win) {
    int y, x;
    getmaxyx(win, y, x);
    return {y, x};
}
