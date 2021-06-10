#include "EventObserver.h"
#include "../../Log/UserLogger.h"

UserLogger* logger;

EventObserver::EventObserver(EventObserver * par)
    :parent(par) {
    logger = UserLogger::getLogger();
}

void EventObserver::emitParent(std::string a, long b) {
#ifdef DEBUG
    logger->logInfo(UserLogger::getString({"event wystrzelony u rodzica: ", a, ", ", std::to_string(b)}));
#endif
    if(parent != nullptr) {
        parent->emit(a, b);
    }
}

void EventObserver::emit(std::string a, long b) {
#ifdef DEBUG
    logger->logInfo(UserLogger::getString({"event wystrzelony: ", a, ", ", std::to_string(b)}));
#endif
    // nie rob nic
}
