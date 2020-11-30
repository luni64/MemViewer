#include "MemoryMap.h"
#include "../elfio/elfio.hpp"
#include "MemoryMap_T3X.h"
#include "MemoryMap_T40.h"

using namespace std;
using namespace ELFIO;

MemoryMap* MemoryMap::MakeMemoryMap(std::string symFilename)
{
    SymTab symTab = parse(symFilename);

    uint32_t teensyType = 0;
    getSymbolValue("_teensy_model_identifier", symTab, &teensyType);

    switch (teensyType)
    {
        case 0x20:                                                                  // LC
            return new MemoryMap_T3X(symTab, 62 * 1024, 8 * 1024, 0x1FFF'F800);     // TLC   62kB flash,   8kB RAM @0x1FFF'F800
        case 0x1D:                                                                  // T3.0
            return new MemoryMap_T3X(symTab, 128 * 1024, 16 * 1024, 0x1FFF'E000);   // T3.0 128kB flash,   16B RAM @0x1FFF'E000
        case 0x21:                                                                  // T3.2
            return new MemoryMap_T3X(symTab, 256 * 1024, 64 * 1024, 0x1FFF'8000);   // T3.2 256kB flash,  64kB RAM @0x1FFF'8000
        case 0x1F:                                                                  // T3.5
            return new MemoryMap_T3X(symTab, 512 * 1024, 262'136, 0x1FFF'0000);     // T3.5 512kB flash,~256kB RAM @0x1FFF'0000
        case 0x22:                                                                  // T3.6
            return new MemoryMap_T3X(symTab, 1024 * 1024, 256 * 1024, 0x1FFF'0000); // T3.6   1MB flash, 256kB RAM @0x1FFF'0000

        case 0x24: // T4.0
            return new MemoryMap_T40(symTab);

        default:
            break;
    }
    return nullptr;
}

vector<Symbol> MemoryMap::parse(std::string symFilename)
{
    SymTab symTab;

    elfio reader;
    section* symTabSection;

    if (reader.load(symFilename) && (symTabSection = reader.sections[".symtab"]) != nullptr)
    {
        const symbol_section_accessor symbols(reader, symTabSection);

        for (unsigned int j = 0; j < symbols.get_symbols_num(); ++j)
        {
            std::string name;
            Elf64_Addr value;
            Elf_Xword size;
            unsigned char bind;
            unsigned char type;
            Elf_Half section_index;
            unsigned char other;
            symbols.get_symbol(j, name, value, size, bind, type, section_index, other);
            if (name != "" && bind != STT_NOTYPE)
            {
                auto sec = reader.sections[section_index];
                string secName = sec != nullptr ? sec->get_name() : "";

                symTab.emplace_back(name, (uint32_t)value, (uint32_t)size, type, bind, secName);
            }
        }
    }

    std::sort(symTab.begin(), symTab.end(), [](Symbol& a, Symbol& b) { return a.size > b.size; });

    copy_if(symTab.begin(), symTab.end(), back_inserter(functions), [](Symbol s) { return s.type == STT_FUNC; });
    copy_if(symTab.begin(), symTab.end(), back_inserter(variables), [](Symbol s) { return s.type == STT_OBJECT; });
    //copy_if(symTab.begin(), symTab.end(), back_inserter(constants), [](Symbol s) { return s.bind == STT_OBJECT && s.section == ".rodata"; });

    return symTab;
}

bool MemoryMap::getSymbolValue(const std::string& name, const std::vector<Symbol>& entries, uint32_t* value)
{
    const Symbol* symbol = getSymbol(name, entries);
    if (symbol != nullptr)
    {
        *value = symbol->value;
        return true;
    }
    return false;
}

const Symbol* MemoryMap::getSymbol(const string& name, const std::vector<Symbol>& entries)
{
    auto itr = find_if(entries.begin(), entries.end(), [&name](const Symbol& e) { return e.name == name; });
    return itr != entries.end() ? &(*itr) : nullptr;
}

SymTab MemoryMap::functions;
SymTab MemoryMap::variables;
SymTab MemoryMap::constants;
