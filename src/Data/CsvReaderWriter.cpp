#include <fstream>
#include <vector>
#include <sstream>
#include "CsvReaderWriter.h"

CsvReader::CsvReader(std::string filename, char separator)
    : filename(std::move(filename)),
    separator(separator) {

}

bool CsvReader::isEof() {
    return curField >= tokens.size();
}

template<typename T>
T CsvReader::getField() {
    throwIfEof();
}

template<> long CsvReader::getField() {
    return std::stol(tokens[curField++]);
}

template<> double CsvReader::getField() {
    return std::stod(tokens[curField++]);
}

template<> std::string CsvReader::getField() {
    return tokens[curField++];
}

template<> bool CsvReader::getField() {
    if(tokens[curField++] == "1"){
        return true;
    }
    if(tokens[curField-1] == "0") {
        return false;
    }
    throw std::runtime_error(tokens[curField-1]);
}

// https://stackoverflow.com/a/1120224
void CsvReader::scan() {
    std::ifstream str{filename, std::ifstream::in};
    std::vector<std::string> result{};
    std::string line;

    if(!str.is_open()) {
        throw std::runtime_error("nie udalo sie otworzyc pliku do odczytu lub plik byl pusty");
    }

    while(std::getline(str,line)) {

        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, separator)) {
            result.push_back(cell);
        }
    }
    tokens = result;
    curField = 0;
}

void CsvReader::throwIfEof() {
    if(isEof()) {
        throw std::runtime_error("brak danych");
    }
}

CsvWriter::CsvWriter(std::string filename, char separator)
    : filename(std::move(filename)),
    separator(separator){

}

void CsvWriter::pushField(std::string field) {
    lineTokens.push_back(std::move(field));
}

void CsvWriter::eol() {
    std::stringstream ss;
    for(int i = 0; i < lineTokens.size(); i++) {
        ss << lineTokens[i];
        if(i != lineTokens.size() - 1) {
            ss << separator;
        }
    }
    ss << std::endl;
    lines.push_back(ss.str());
    lineTokens.clear();
}

void CsvWriter::eof() {
    std::ofstream out{filename};
    if(!out.is_open()) {
        throw std::runtime_error("nie dalo sie otworzyc pliku do zapisu");
    }

    for(auto l : lines) {
        out << l;
    }

    out.close();
    lines.clear();
}
