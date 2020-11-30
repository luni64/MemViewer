#pragma once

#include "MemoryMap.h"

class MemoryMap_T40 : public  MemoryMap
{
 public:
    void print();
    std::string getSymbols() { return std::string(""); }

 protected:
    uint32_t ITCM_start, ITCM_used, ITCM_end;
    uint32_t DTCM_start, DTCM_used, DTCM_end;
    uint32_t DMAM_start, DMAM_used, DMAM_end;

    MemoryMap_T40(const SymTab&);
    friend MemoryMap;
};
