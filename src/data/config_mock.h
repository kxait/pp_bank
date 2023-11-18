#ifndef PP_BANK_CONFIGMOCK_H
#define PP_BANK_CONFIGMOCK_H

#include "..\dalc\config_dalc.h"

class config_mock : public config_dalc {
    static std::map<std::string, std::string> m_data;
public:
    std::map<std::string, std::string> get_data() override;
    config* get_config() override;
    std::string get_location() override;
};


#endif //PP_BANK_CONFIGMOCK_H
