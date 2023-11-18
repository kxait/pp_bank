#ifndef PP_BANK_CONFIGDALC_H
#define PP_BANK_CONFIGDALC_H

#include <map>
#include "../config.h"

class config_dalc {
public:
    virtual std::map<std::string, std::string> get_data() = 0;
    virtual config* get_config() = 0;
    virtual std::string get_location() = 0;
};


#endif //PP_BANK_CONFIGDALC_H
