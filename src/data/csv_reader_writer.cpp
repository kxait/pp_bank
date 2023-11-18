#include <fstream>
#include <vector>
#include <sstream>
#include "csv_reader_writer.h"

csv_reader::csv_reader(std::string filename, char separator)
    : m_filename(std::move(filename)),
    m_separator(separator) {

}

bool csv_reader::is_eof() {
    return m_curField >= m_tokens.size();
}

template<typename T>
T csv_reader::get_field() {
    throw_if_eof();
    return {};
}

template<> long csv_reader::get_field() {
    return std::stol(m_tokens[m_curField++]);
}

template<> double csv_reader::get_field() {
    return std::stod(m_tokens[m_curField++]);
}

template<> std::string csv_reader::get_field() {
    return m_tokens[m_curField++];
}

template<> bool csv_reader::get_field() {
    if(m_tokens[m_curField++] == "1"){
        return true;
    }
    if(m_tokens[m_curField-1] == "0") {
        return false;
    }
    throw std::runtime_error(m_tokens[m_curField-1]);
}

// https://stackoverflow.com/a/1120224
void csv_reader::scan() {
    std::ifstream str{m_filename, std::ifstream::in};
    std::vector<std::string> result{};
    std::string line;

    if(!str.is_open()) {
        throw std::runtime_error("nie udalo sie otworzyc pliku do odczytu lub plik byl pusty");
    }

    while(std::getline(str,line)) {

        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, m_separator)) {
            result.push_back(cell);
        }
    }
    m_tokens = result;
    m_curField = 0;
}

void csv_reader::throw_if_eof() {
    if(is_eof()) {
        throw std::runtime_error("brak danych");
    }
}

csv_writer::csv_writer(std::string filename, const char separator)
    : m_filename(std::move(filename)),
    m_separator(separator){

}

void csv_writer::push_field(std::string field) {
    m_line_tokens.push_back(std::move(field));
}

void csv_writer::eol() {
    std::stringstream ss;
    for(int i = 0; i < m_line_tokens.size(); i++) {
        ss << m_line_tokens[i];
        if(i != m_line_tokens.size() - 1) {
            ss << m_separator;
        }
    }
    ss << std::endl;
    m_lines.push_back(ss.str());
    m_line_tokens.clear();
}

void csv_writer::eof() {
    std::ofstream out{m_filename};
    if(!out.is_open()) {
        throw std::runtime_error("nie dalo sie otworzyc pliku do zapisu");
    }

    for(const auto& l : m_lines) {
        out << l;
    }

    out.close();
    m_lines.clear();
}
