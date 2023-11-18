#ifndef PP_BANK_CONFIG_H
#define PP_BANK_CONFIG_H

#include<string>
#include<map>

class Config {
    std::map<std::string, std::string> config;
public:
    Config(std::map<std::string, std::string>);
    bool exists(std::string);
    std::string get(std::string);
};


#endif //PP_BANK_CONFIG_H
