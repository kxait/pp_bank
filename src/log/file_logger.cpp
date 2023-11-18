#include "file_logger.h"
#include<iostream>

file_logger::file_logger(std::string file, std::string format)
    : logger(std::move(format)),
      m_filename(std::move(file)),
      m_file_handle(m_filename, std::ofstream::out | std::ofstream::app) {
    if(!m_file_handle.is_open()) {
        throw std::runtime_error("nie udalo sie otworzyc pliku");
    }
}

void file_logger::log(const log_level_t level, const std::string message) {
    const auto m = logger::get_formatted_message(message, level);
    m_file_handle << m << std::endl;
}

file_logger::~file_logger() {
    m_file_handle.close();
}
