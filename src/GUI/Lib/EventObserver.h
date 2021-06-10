#ifndef PP_BANK_EVENTOBSERVER_H
#define PP_BANK_EVENTOBSERVER_H

#include<string>

class EventObserver {
protected:
    EventObserver* parent;
public:
    EventObserver(EventObserver* = nullptr);
    virtual void emit(std::string, long);
    virtual void emitParent(std::string, long);
};


#endif //PP_BANK_EVENTOBSERVER_H
