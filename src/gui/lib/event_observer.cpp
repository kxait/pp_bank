#include "event_observer.h"

#include "../../log/user_logger.h"

user_logger* logger;

event_observer::event_observer(event_observer * par)
    :m_parent(par) {
    logger = user_logger::get_logger();
}

void event_observer::emit_parent(std::string a, long b) {
#ifdef DEBUG
    logger->logInfo(UserLogger::getString({"event wystrzelony u rodzica: ", a, ", ", std::to_string(b)}));
#endif
    if(m_parent != nullptr) {
        m_parent->emit(std::move(a), b);
    }
}

void event_observer::emit(std::string a, long b) {
#ifdef DEBUG
    logger->logInfo(UserLogger::getString({"event wystrzelony: ", a, ", ", std::to_string(b)}));
#endif
    // nie rob nic
}
