#include "builder.h"
#include <Windows.h>
#include <filesystem>
#include "../logger.h"

struct rsdsGUID
{
    uint32_t head;
    uint16_t prol;
    uint16_t epil;
    unsigned char unk[8];
};

#pragma pack(push, 1)
typedef struct
{
    uint32_t    Signature;     
    uint8_t     GUID[16];
    uint32_t    Age;   
    char        PDBName[MAX_PATH];
} RSDS_HEADER;
#pragma pack(pop)

std::string builder_c::unity_url_path = "http://symbolserver.unity3d.com/"; // + NAME.pdb/ + GUID_AGE/ + NAME.pdb

std::string builder_c::get_symbols_url(std::vector<uint8_t> binary, std::string& out_file_name) {
    if (binary.empty()) {
        spdlog::critical("Binary is empty.");
        return std::string();
    }
    
    auto find_rsds = [] (uint8_t* data, uint8_t* data_end) ->  RSDS_HEADER* {
        unsigned char rsds_signature[] = {'R', 'S', 'D', 'S'};

        while (data < data_end) {
            if (memcmp(rsds_signature, data, sizeof(rsds_signature)) == 0) {
                RSDS_HEADER* header = (RSDS_HEADER*)(data);
                if (std::string(header->PDBName).find(".pdb") != std::string::npos) {
                    return header;
                }
            }
            data++;
        }
        spdlog::critical("Failed to find RSDS pattern. I don't really think file contains debug info...");
        return nullptr;
    };

    auto extract_guid = [] (RSDS_HEADER* rsds) -> std::string {
        char buffer[255];
        rsdsGUID* guid = (rsdsGUID*)rsds->GUID;
        snprintf(buffer, sizeof(buffer), "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X%X", 
                 guid->head, guid->prol, guid->epil, guid->unk[0], guid->unk[1], guid->unk[2],
                 guid->unk[3], guid->unk[4], guid->unk[5], guid->unk[6], guid->unk[7], rsds->Age);

        return std::string(buffer);
    };

    RSDS_HEADER* rsds = find_rsds(binary.data(), binary.data() + binary.size());
    if (!rsds) {
        return std::string();
    }
    
    std::string file_name = std::filesystem::path(rsds->PDBName).filename().string();
    file_name = file_name.erase(file_name.size() - 4);
    std::string guid_age = extract_guid(rsds);
    std::stringstream stream; stream << unity_url_path << file_name << ".pdb/" << guid_age << "/" << file_name << ".pd_";
    out_file_name = file_name;
    return stream.str();
} 