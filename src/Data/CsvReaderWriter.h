#ifndef PP_BANK_CSVREADERWRITER_H
#define PP_BANK_CSVREADERWRITER_H
#include<iostream>

class CsvReader {
    std::string filename;
    char separator;
    std::vector<std::string> tokens;
    long curField;
    void throwIfEof();
public:
    explicit CsvReader(std::string filename, char separator = ';');
    void scan();
    bool isEof();
    template<typename T>
    T getField();
};

class CsvWriter {
    std::string filename;
    char separator;
    std::vector<std::string> lineTokens;
    std::vector<std::string> lines;
public:
    explicit CsvWriter(std::string filename, char separator = ';');
    void pushField(std::string field);
    void eol();
    void eof();
};


#endif //PP_BANK_CSVREADERWRITER_H
