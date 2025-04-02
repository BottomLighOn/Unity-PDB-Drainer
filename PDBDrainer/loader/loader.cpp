#include "loader.h"
#include <iostream>
#include "../logger.h"

int loader_c::load_binary(const std::string& path, std::vector<uint8_t>& out_binary) {
    FILE* file;
    auto error = fopen_s(&file, path.c_str(), "rb");
    if (!file) {
        spdlog::critical("Failed to open file {} Error: {}", path.c_str(), error);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    uint64_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (file_size <= 0) {
        spdlog::critical("Empty File");
        fclose(file);
        return -1;
    }

    std::vector<uint8_t> binary(file_size);
    fread(binary.data(), 1, file_size, file);
    fclose(file);
    
    out_binary = binary;
    return 0;
}