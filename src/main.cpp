#include "Analyzers/MemoryMap.h"
#include <string>

int main(int argc, const char* argv[])
{
    std::string elfFile = argc > 1 ? argv[1] : "tttestLC.elf";

    auto map = MemoryMap::MakeMemoryMap(elfFile);

    if (map != nullptr)
    {
        map->print();
    }
    else
    {
        printf("Error reading %s\n", elfFile.c_str());
    }

    char i;
    scanf_s("%c", &i, 1);

    return 0;
}