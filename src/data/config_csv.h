#ifndef PP_BANK_CONFIGCSV_H
#define PP_BANK_CONFIGCSV_H

#include "../dalc/config_dalc.h"

class config_csv : public config_dalc {
    std::string m_filename;
    char m_separator;
public:
    explicit config_csv(const std::string&, char = ';');
    std::map<std::string, std::string> get_data() override;
    config* get_config() override;
    std::string get_location() override;
};


#endif //PP_BANK_CONFIGCSV_H
