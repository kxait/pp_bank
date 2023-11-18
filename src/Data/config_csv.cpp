#include "config_csv.h"
#include "csv_reader_writer.h"

ConfigCsv::ConfigCsv(std::string file, char sep)
    : filename(file),
    separator(sep) {

}

std::map<std::string, std::string> ConfigCsv::getData() {
    auto result = std::map<std::string, std::string>{};
    CsvReader input(filename, separator);
    input.scan();
    // id val
    while(!input.isEof()) {
        auto id = input.getField<std::string>();
        auto val = input.getField<std::string>();
        result[id] = val;
    }
    return result;
}

Config *ConfigCsv::getConfig() {
    return new Config(getData());
}

std::string ConfigCsv::getLocation() {
    return filename;
}
