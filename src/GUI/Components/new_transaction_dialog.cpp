#include "new_transaction_dialog.h"
#include "input_field.h"
#include "../Lib/ScreenProps.h"
#include "menu_horizontal.h"
#include "..\..\Log\user_logger.h"

NewTransactionDialog::NewTransactionDialog(
        int y,
        int x,
        int h,
        int w,
        EventObserver * par,
        std::string srcValue,
        std::string destValue)
    : Component(y,x,h,w,par){
    keypad(win, true);
    fields = {
            dynamic_cast<Component*>(new InputField(y+2, x+1, 1, width-2, this, srcValue)),
            dynamic_cast<Component*>(new InputField(y+4, x+1, 1, width-2, this, destValue)),
            dynamic_cast<Component*>(new InputField(y+6, x+1, 1, width-2, this)),
            dynamic_cast<Component*>(MenuHorizontal::produce(y+height-2, x+1, {
                "Ok",
                "Anuluj"
            }, this))
    };
    fields[focusedField]->focus();
}

long validateFieldLong(InputField* a) {
    auto val = a->getValue();
    return std::stol(val);
}

double validateFieldFloat(InputField* a) {
    auto val = a->getValue();
    return std::stod(val);
}

Transaction NewTransactionDialog::getData() {
    long sId, dId;
    double am;
    try {
        sId = validateFieldLong(dynamic_cast<InputField*>(fields[0]));
        dId = validateFieldLong(dynamic_cast<InputField*>(fields[1]));
        am = validateFieldFloat(dynamic_cast<InputField*>(fields[2]));
    }catch(const std::exception& e) {
        auto logger = UserLogger::getLogger();
        logger->logError(UserLogger::getString({
            "nie udalo sie stworzyc tranzakcji z formatki (sId: ",
            dynamic_cast<InputField*>(fields[0])->getValue(),
            ", dId: ",
            dynamic_cast<InputField*>(fields[1])->getValue(),
            ", am: ",
            dynamic_cast<InputField*>(fields[2])->getValue(),
            ")",
        }));
        throw e;
    }

    return {0, sId, dId, am};
}

void NewTransactionDialog::emit(std::string a, long b) {
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

void NewTransactionDialog::handleInput(int a) {
    if(a == KEY_DOWN) {
        rotateFocusedField();
    }else if(a == KEY_UP) {
        rotateFocusedField(false);
    }else{
        fields[focusedField]->handleInput(a);
    }
}

void NewTransactionDialog::render() {
    mvwprintw(win, 0, 1, "Nowa transakcja");
    mvwprintw(win, 1, 1, "Id konta zrodlowego");
    mvwprintw(win, 3, 1, "Id konta docelowego");
    mvwprintw(win, 5, 1, "Wartosc");
    wrefresh(win);
    for(auto i : fields) {
        i->render();
    }
}

NewTransactionDialog NewTransactionDialog::produce(std::string src, std::string dst) {
    auto props = ScreenProps::get();
    return NewTransactionDialog(1, 1, props.Height()-2, props.Width()-2, nullptr, src, dst);
}

Transaction NewTransactionDialog::getResult(std::string src, std::string dst) {
    auto p = produce(src, dst);
    auto result = p.act();
    if(result == 1) {
        return p.getData();
    }
    throw std::runtime_error("dialog zakonczyl sie anulacja");
}

long NewTransactionDialog::act() {
    int c;
    render();
    while((c = getInput()) != 0 && !end) {
        handleInput(c);
        render();
        if(end) break; // z jakiegos powodu warunek '!end' nie byl lapany na linii 109, wiec musimy tutaj sprawdzic czy sie nie zakonczylo
    }
    return end;
}

void NewTransactionDialog::rotateFocusedField(bool down) {
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

void NewTransactionDialog::setFieldValue(int a, std::string b) {
    if(a < 3 && a >= 0) {
        dynamic_cast<InputField*>(fields[a])->setValue(b);
    }
}
