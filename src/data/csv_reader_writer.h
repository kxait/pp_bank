#ifndef PP_BANK_CSVREADERWRITER_H
#define PP_BANK_CSVREADERWRITER_H

class csv_reader {
    std::string m_filename;
    char m_separator;
    std::vector<std::string> m_tokens;
    long m_curField;
    void throw_if_eof();
public:
    explicit csv_reader(std::string filename, char separator = ';');
    void scan();
    bool is_eof();
    template<typename T>
    T get_field();
};

class csv_writer {
    std::string m_filename;
    char m_separator;
    std::vector<std::string> m_line_tokens;
    std::vector<std::string> m_lines;
public:
    explicit csv_writer(std::string filename, char separator = ';');
    void push_field(std::string field);
    void eol();
    void eof();
};


#endif //PP_BANK_CSVREADERWRITER_H
