#include "MemoryMap_T40.h"
#include <stdio.h>

MemoryMap_T40::MemoryMap_T40(const SymTab& symTab)
{
    if (!getSymbolValue("_stext", symTab, &ITCM_start)) return;
    if (!getSymbolValue("_etext", symTab, &ITCM_used)) return;

    if (!getSymbolValue("_sdata", symTab, &DTCM_start)) return;
    if (!getSymbolValue("_ebss", symTab, &DTCM_used)) return;
    if (!getSymbolValue("_estack", symTab, &DTCM_end)) return;
}

void MemoryMap_T40::print()
{
    printf(" ------------------------------------------------------------------------------\n");
    printf(" | Type   |   Used    |   start    |    end     | Remarks                      |\n");
    printf(" |-----------------------------------------------------------------------------|\n");
    printf(" | On chip RAM (RAM1), 512kB       |            |                              |\n");
    printf(" |-----------------------------------------------------------------------------|\n");
    printf(" | ITCM   |%7.1f kB | 0x%08X | 0x%08X | fastrun Code                 |\n", (ITCM_used - ITCM_start) / 1024.0, ITCM_start, ITCM_end);
    printf(" | DTCM   |%7.1f kB | 0x%08X | 0x%08X | global and static variables  | \n", (DTCM_used - DTCM_start) / 1024.0, DTCM_start, DTCM_end);
    printf(" | STACK  |    ---    | 0x%08X | 0x%08X | local variables              |\n", DTCM_end, ITCM_start + 512 * 1024);
    printf(" |-----------------------------------------------------------------------------|\n");
    printf(" | Off chip RAM (OCRAM), 512kB                                                 |\n");
    printf(" |-----------------------------------------------------------------------------|\n");
    printf(" | DMAMEM |%7.1f kB | 0x%08X | 0x%08X | DMAMEM globals, TD-buffers...|\n", (ITCM_used - ITCM_start) / 1024.0, ITCM_start, ITCM_end);
    printf(" | HEAP   |%7.1f kB | 0x%08X | 0x%08X | malloc / new                 |\n", (DTCM_used - DTCM_start) / 1024.0, DTCM_start, DTCM_end);
    printf(" |-----------------------------------------------------------------------------|\n");
    printf(" | Program memory, 1900kB                                                     |\n");
    printf(" |-----------------------------------------------------------------------------|\n");
    printf(" | FLASH  |%7.1f kB | 0x%08X | 0x%08X | DMAMEM globals, TD-buffers...|\n", (ITCM_used - ITCM_start) / 1024.0, ITCM_start, ITCM_end);
    printf("  -----------------------------------------------------------------------------\n");
}