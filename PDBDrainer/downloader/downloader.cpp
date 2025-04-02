#include "downloader.h"
#include <iostream>
#include <Windows.h>
#include <wininet.h>
#include "../logger.h"

int downloader_c::download_pdb(const std::string& packed_pdb_url, const std::string& packed_pdb_name) {
    auto internet_handle = InternetOpenA("Downloader", INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
    if (!internet_handle) {
        spdlog::critical("Failed to open internet handle. Error {}", GetLastError());
        return -1;
    }

    auto url_handle = InternetOpenUrlA(internet_handle, packed_pdb_url.c_str(), nullptr, 0, INTERNET_FLAG_RELOAD, 0);
    if (!url_handle) {
        spdlog::critical("Failed to open URL handle. Error: {}", GetLastError());
        InternetCloseHandle(internet_handle);
        return -1;
    }

    unsigned char temp_buffer[4096];
    memset(temp_buffer, 0, sizeof(temp_buffer));
    DWORD bytes_read = 0;

    FILE* output_file_handle = 0;
    auto file_open_error = fopen_s(&output_file_handle, packed_pdb_name.c_str(), "wb");
    if (!output_file_handle) {
        spdlog::critical("Failed tocreate pd_ file. Error: {}", file_open_error);
        InternetCloseHandle(url_handle);
        InternetCloseHandle(internet_handle);
        return -1;
    }

    while (InternetReadFile(url_handle, temp_buffer, sizeof(temp_buffer), &bytes_read) && bytes_read > 0) {
        static bool is_first_attempt = true;
        if (is_first_attempt && bytes_read <= 15) {
            std::string response((char*)temp_buffer, bytes_read);
            if (response.contains("Not found")) {
                spdlog::critical("PDB File does not exist on Unity Symbols Server");
                InternetCloseHandle(url_handle);
                InternetCloseHandle(internet_handle);
                fclose(output_file_handle);
                if (!DeleteFileA(packed_pdb_name.c_str())) {
                    spdlog::error("Failed to delete Packed PDB. Error: {}", GetLastError());
                }
                return -1;
            }
            is_first_attempt = false;
        }
        
        fwrite(temp_buffer, 1, bytes_read, output_file_handle);
    }

    InternetCloseHandle(url_handle);
    InternetCloseHandle(internet_handle);
    fclose(output_file_handle);

    return 0;
}