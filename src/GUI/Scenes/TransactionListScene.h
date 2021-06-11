#ifndef PP_BANK_TRANSACTIONLISTSCENE_H
#define PP_BANK_TRANSACTIONLISTSCENE_H


#include "../Lib/Scene.h"
#include "../Lib/SceneComposer.h"
#include "../../BankManager.h"

class TransactionListScene : public Scene {
    BankManager* man;
    std::vector<Transaction> transactions;
    std::vector<AccountWithBalance> accounts;
    std::vector<Component*> components;
    int focusedIndex = 0;
    void render();
    void rotateFocusedIndex();
    void createComponents();
public:
    TransactionListScene(SceneComposer*, BankManager*);
    long act() override;
    void emit(std::string, long) override;
};


#endif //PP_BANK_TRANSACTIONLISTSCENE_H
