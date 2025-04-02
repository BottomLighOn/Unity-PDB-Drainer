#ifndef LOADER_H
#define LOADER_H
#include <string>
#include <vector>

class loader_c
{
public:
    static int load_binary(const std::string& path, std::vector<uint8_t>& out_binary);
};
#endif // !LOADER_H
