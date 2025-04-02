#ifndef BUILDER_H
#define BUILDER_H
#include <string>
#include <sstream>
#include <vector>

class builder_c
{
    static std::string unity_url_path;
public:
    static std::string get_symbols_url(std::vector<uint8_t> binary, std::string& out_file_name);
};

#endif
