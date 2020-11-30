#pragma once

#include "MemoryMap.h"
#include <vector>
#include "Symbol.h"

class MemoryMap_T3X : public  MemoryMap
{
 public:
    void print() override;
    std::string getSymbols() override;

 protected:
    uint32_t RAM_start, RAM_used, RAM_end;
    uint32_t FLASH_start, FLASH_used, FLASH_end;

   
    MemoryMap_T3X(SymTab& symTab, uint32_t flash_size, uint32_t ram_size, uint32_t ram_start);
    friend MemoryMap;
};
