#ifndef PP_BANK_CONFIGMOCK_H
#define PP_BANK_CONFIGMOCK_H

#include "..\DALC\config_dalc.h"

class ConfigMock : public ConfigDALC {
    static std::map<std::string, std::string> data;
public:
    std::map<std::string, std::string> getData() override;
    Config* getConfig() override;
    std::string getLocation() override;
};


#endif //PP_BANK_CONFIGMOCK_H
