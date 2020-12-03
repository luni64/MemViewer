#include "Analyzers/Symbol.h"
#include "fmt/format.h"
#include <fstream>
#include <string>

using namespace std;

bool parseSymTab(ifstream& file)
{
    string line;
    while (getline(file, line) && line != "SYMBOL TABLE:") {} // skip all lines before the symbol table

    SymTab absSymbols;
    SymTab functions;
    SymTab variables;

    while (getline(file, line) && line !="")
    {
        try
        {
            uint32_t value = strtol(line.substr(0, 8).c_str(), nullptr, 16);    // value = bytes [00-07]
            string flags = line.substr(9, 7);                                   // flags = bytes [09-16}]

            int idx = line.find('\t');
            string section = line.substr(17, idx - 17);                         // section = bytes 17 up to next tab
            uint32_t size = strtol(line.substr(idx + 1, 8).c_str(),nullptr,16); // size = bytes from tab 
            string name = line.substr(idx + 9);

            if (flags[5] != 'd')
            {
                switch (flags[6])
                {
                    case 'F':
                        functions.emplace_back(name, value, size, 'F', '\0', section);
                        break;
                    case 'O':
                        variables.emplace_back(name, value, size, 'O', '\0', section);
                        break;
                    case ' ':
                        absSymbols.emplace_back(name, value, size, ' ', '\0', section);
                        break;
                    default:
                        break;
                }
            }
        } catch (const std::exception& e)
        {

        }

        //fmt::print("v:{} l:{} n:{} s:{}\n", value, size, name, section);
    }

    return true;
}

bool parseObjDump(string dumpFile)
{
    ifstream file(dumpFile);
    if (!file.is_open()) return false;

    parseSymTab(file);

    file.close();

    return true;
}