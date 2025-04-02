#include <iostream>
#include <Windows.h>
#include <wininet.h>
#include <filesystem>
#include "logger.h"
#include "loader/loader.h"
#include "builder/builder.h"
#include "downloader/downloader.h"
#include "expander/expander.h"

int main(int argc, char* argv[]) {

    auto console = spdlog::stdout_color_mt("global");
    spdlog::set_default_logger(console);
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");

    if (argc < 2) {
        console->critical("Failed to get arguments!");
        console->info("Usage: {} <PE>", std::filesystem::path(argv[0]).filename().string().c_str());
        if (getchar()) {
            return -1;
        }
    }

    console->info("[Welcome to Unity PDB Drainer!]\n");
    console->info("Opening File: {}", argv[1]);
    
    do {
        std::vector<uint8_t> binary;
        int load_status = loader_c::load_binary(argv[1], binary);
        if (load_status != 0) {
            console->critical("Failed to load binary");
            break;
        }

        console->info("File size: {}", binary.size());

        std::string pdb_name = std::string();
        std::string packed_pdb_url = builder_c::get_symbols_url(binary, pdb_name);
        if (packed_pdb_url.empty()) {
            console->critical("Failed to get URL.");
            break;
        }

        std::string packed_pdb_name = pdb_name + ".pd_";
        std::string unpacked_pdb_name = pdb_name + ".pdb";

        console->info("Packed PDB URL: {}", packed_pdb_url.c_str());
        console->info("Downloading file...");

        int download_result = downloader_c::download_pdb(packed_pdb_url, packed_pdb_name);
        if (download_result != 0) {
            console->critical("Failed to download pdb.");
            break;
        }

        console->info("Successfully downloaded file");

        int expand_result = expander_c::expand_pdb(packed_pdb_name, unpacked_pdb_name);
        if (expand_result != 0) {
            console->critical("Failed to expand resiult");
            break;
        }

        if (!DeleteFileA(packed_pdb_name.c_str())) {
            console->error("Failed to delete Packed PDB. Error: {}", GetLastError());
            break;
        }

        console->info("Packed PDB deleted successfully.");
        console->info("Finished, have a nice day!");
        console->info("Press enter to leave...");

        if (getchar()) {};
        return 0;
    } while (false);

    
    if (getchar()) {};
    return -1;
}
