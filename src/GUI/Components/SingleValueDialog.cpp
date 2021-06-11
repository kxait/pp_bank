#include "SingleValueDialog.h"
#include "InputField.h"
#include "MenuHorizontal.h"
#include "../Lib/ScreenProps.h"

void SingleValueDialog::rotateFocusedField(bool down) {
    fields[focusedField]->removeFocus();
    if(down) {
        focusedField++;
    }else{
        focusedField--;
    }
    if(focusedField == fields.size()) {
        focusedField = 0;
    }
    if(focusedField < 0) {
        focusedField = fields.size() - 1;
    }
    fields[focusedField]->focus();
}

SingleValueDialog::SingleValueDialog(int y, int x, int h, int w, EventObserver * par, std::string title, std::string startValue)
    : Component(y, x, h, w, par),
      title(title) {
    keypad(win, true);
    fields = {
        dynamic_cast<Component*>(new InputField(y+2, x+1, 1, width-2, this, startValue)),
        dynamic_cast<Component*>(MenuHorizontal::produce(y+height-2, x+1, {
            "Ok",
            "Anuluj"
        }, this))
    };

    fields[0]->focus();
}

std::string SingleValueDialog::getData() {
    return dynamic_cast<InputField*>(fields[0])->getValue();
}

void SingleValueDialog::emit(std::string a, long b) {
    if(a == "choice") {
        switch(b) {
            case 0: { // ok
                end = 1;
                break;
            }
            case 1: { // anuluj
                end = 2;
                break;
            }
        }
    }
}

void SingleValueDialog::handleInput(int a) {
    if(a == KEY_DOWN) {
        rotateFocusedField();
    }else if(a == KEY_UP) {
        rotateFocusedField(false);
    }else{
        fields[focusedField]->handleInput(a);
    }
}

void SingleValueDialog::render() {
    mvwprintw(win, 0, 0, title.data());
    wrefresh(win);
    for(auto i : fields) {
        i->render();
    }
}

void SingleValueDialog::setFieldValue(std::string a) {
    dynamic_cast<InputField*>(fields[0])->setValue(a);
}

SingleValueDialog SingleValueDialog::produce(std::string title, std::string startValue) {
    auto props = ScreenProps::get();

    // min 15
    auto w = (title.size() > 15 ? title.size() : 15);
    auto h = 6;
    auto posY = props.Height() / 2 - h / 2;
    auto posX = props.Width() / 2 - w / 2;
    return SingleValueDialog(posY, posX, h, w, nullptr, title, startValue);
}

std::string SingleValueDialog::getResult(std::string title, std::string startValue) {
    auto p = produce(title, startValue);
    auto result = p.act();
    if(result == 1) {
        return p.getData();
    }
    throw std::runtime_error("dialog zakonczyl sie anulacja");
}

long SingleValueDialog::act() {
    int c;
    render();
    while((c = getInput()) != 0 && !end) {
        handleInput(c);
        render();
        if(end) break; // z jakiegos powodu warunek '!end' nie byl lapany na linii 109, wiec musimy tutaj sprawdzic czy sie nie zakonczylo
    }
    return end;
}
