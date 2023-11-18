#ifndef PP_BANK_CONFIG_H
#define PP_BANK_CONFIG_H

#include<string>
#include<map>

class config {
    std::map<std::string, std::string> m_config;
public:
    explicit config(std::map<std::string, std::string>);
    bool exists(const std::string&);
    std::string get(const std::string&);
};


#endif //PP_BANK_CONFIG_H
