#ifndef PP_BANK_CONFIGDALC_H
#define PP_BANK_CONFIGDALC_H

#include <vector>
#include <map>
#include "../config.h"

class ConfigDALC {
public:
    virtual std::map<std::string, std::string> getData() = 0;
    virtual Config* getConfig() = 0;
    virtual std::string getLocation() = 0;
};


#endif //PP_BANK_CONFIGDALC_H
