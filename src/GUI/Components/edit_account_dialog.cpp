#include "edit_account_dialog.h"

#include "new_transaction_dialog.h"
#include "input_field.h"
#include "../Lib/ScreenProps.h"
#include "menu_horizontal.h"
#include "..\..\Log\user_logger.h"

void EditAccountDialog::rotateFocusedField(bool down) {
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

EditAccountDialog::EditAccountDialog(int y, int x, int h, int w, EventObserver * par, std::string name, std::string pesel, std::string title)
    : Component(y,x,h,w,par),
    title(title) {
    keypad(win, true);
    fields = {
            dynamic_cast<Component*>(new InputField(y+2, x+1, 1, width-2, this, name)),
            dynamic_cast<Component*>(new InputField(y+4, x+1, 1, width-2, this, pesel)),
            dynamic_cast<Component*>(MenuHorizontal::produce(y+height-2, x+1, {
                    "Ok",
                    "Anuluj"
            }, this))
    };
    fields[focusedField]->focus();
}

Account EditAccountDialog::getData() {
    std::string name, pesel;
    double am;
    try {
        name = dynamic_cast<InputField*>(fields[0])->getValue();
        pesel = dynamic_cast<InputField*>(fields[1])->getValue();
    }catch(const std::exception& e) {
        auto logger = UserLogger::getLogger();
        logger->logError(UserLogger::getString({
            "nie udalo sie stworzyc konta z formatki (imienazwisko: ",
            dynamic_cast<InputField*>(fields[0])->getValue(),
            ", pesel: ",
            dynamic_cast<InputField*>(fields[1])->getValue(),
            ")",
        }));
        throw e;
    }

    return {0, name, pesel, false};
}

void EditAccountDialog::emit(std::string a, long b) {
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

void EditAccountDialog::handleInput(int a) {
    if(a == KEY_DOWN) {
        rotateFocusedField();
    }else if(a == KEY_UP) {
        rotateFocusedField(false);
    }else{
        fields[focusedField]->handleInput(a);
    }
}

void EditAccountDialog::render() {
    mvwprintw(win, 0, 1, title.data());
    mvwprintw(win, 1, 1, "Nazwa konta");
    mvwprintw(win, 3, 1, "PESEL posiadacza konta");
    wrefresh(win);
    for(auto i : fields) {
        i->render();
    }
}

void EditAccountDialog::setFieldValue(int a, std::string b) {
    if(a < 2 && a >= 0) {
        dynamic_cast<InputField*>(fields[a])->setValue(b);
    }
}

EditAccountDialog EditAccountDialog::produce(std::string name, std::string pesel, std::string title) {
    auto props = ScreenProps::get();
    return {1, 1, props.Height()-2, props.Width()-2, nullptr, name, pesel, title};
}

Account EditAccountDialog::getResult(std::string name, std::string pesel, std::string title) {
    auto p = produce(name, pesel, title);
    auto result = p.act();
    if(result == 1) {
        return p.getData();
    }
    throw std::runtime_error("dialog zakonczyl sie anulacja");
}

long EditAccountDialog::act() {
    int c;
    render();
    while((c = getInput()) != 0 && !end) {
        handleInput(c);
        render();
        if(end) break; // z jakiegos powodu warunek '!end' nie byl lapany na linii 109, wiec musimy tutaj sprawdzic czy sie nie zakonczylo
    }
    return end;
}