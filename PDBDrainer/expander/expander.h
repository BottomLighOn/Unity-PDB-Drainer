#ifndef EXPANDER_H
#define EXPANDER_H
#include <string>
class expander_c
{
public:
   static int expand_pdb(const std::string& pdb_packed_name, const std::string& pdb_unpacked_name);
};
#endif // !EXPANDER_H
