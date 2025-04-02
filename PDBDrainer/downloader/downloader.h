#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include <string>

class downloader_c
{
public:
    static int download_pdb(const std::string& packed_pdb_url, const std::string& packed_pdb_name);
};
#endif // !DOWNLOADER_H
