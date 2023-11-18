#ifndef PP_BANK_CONFIGCSV_H
#define PP_BANK_CONFIGCSV_H

#include "..\DALC\config_dalc.h"

class ConfigCsv : public ConfigDALC {
    std::string filename;
    char separator;
public:
    ConfigCsv(std::string, char = ';');
    std::map<std::string, std::string> getData() override;
    Config* getConfig() override;
    std::string getLocation() override;
};


#endif //PP_BANK_CONFIGCSV_H
