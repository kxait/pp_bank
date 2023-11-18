#include "config_csv.h"
#include "csv_reader_writer.h"

config_csv::config_csv(const std::string&file, const char sep)
    : m_filename(file),
    m_separator(sep) {

}

std::map<std::string, std::string> config_csv::get_data() {
    auto result = std::map<std::string, std::string>{};
    csv_reader input(m_filename, m_separator);
    input.scan();
    // id val
    while(!input.is_eof()) {
        auto id = input.get_field<std::string>();
        const auto val = input.get_field<std::string>();
        result[id] = val;
    }
    return result;
}

config *config_csv::get_config() {
    return new config(get_data());
}

std::string config_csv::get_location() {
    return m_filename;
}
