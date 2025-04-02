#include "expander.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include "../logger.h"

int expander_c::expand_pdb(const std::string& packed_pdb_name, const std::string& unpacked_pdb_name) {
    std::stringstream shell_command;
    shell_command << "expand \"" << packed_pdb_name << "\" \"" << unpacked_pdb_name << "\"";
    std::string process_command = shell_command.str();

    STARTUPINFOA si = {sizeof(si)};
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(0, (char*)process_command.c_str(), 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &si, &pi)) {
        spdlog::error("Failed to create process for expanding packed file.");
        spdlog::info("You can try manually call \"{}\" to unpack packed PDB", shell_command.str().c_str());
        return -1;
    }
    spdlog::info("I am unpacking PDB right now, it may take a while...");

    WaitForSingleObject(pi.hProcess, INFINITE);

    spdlog::info("We are done, but i need to delete packed pdb and do some cleanup, wait a sec...");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}