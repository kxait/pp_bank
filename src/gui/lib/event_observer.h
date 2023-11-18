#ifndef PP_BANK_EVENTOBSERVER_H
#define PP_BANK_EVENTOBSERVER_H

#include<string>

class event_observer {
protected:
    event_observer* m_parent;
public:
    explicit event_observer(event_observer* = nullptr);
    virtual void emit(std::string, long);
    virtual void emit_parent(std::string, long);
};


#endif //PP_BANK_EVENTOBSERVER_H
