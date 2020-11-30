#include "MemoryMap_T3X.h"
#include "../helpers.h"
#include "fmt/format.h"
#include "fort.hpp"
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;
using namespace fort;

MemoryMap_T3X::MemoryMap_T3X(SymTab& symTab, uint32_t flash_size, uint32_t ram_size, uint32_t ram_start)
{
    RAM_start = ram_start;
    RAM_end = RAM_start + ram_size;
    if (!getSymbolValue("_ebss", symTab, &RAM_used)) return;

    FLASH_start = 0x0000'0000;
    FLASH_end = FLASH_start + flash_size;
    if (!getSymbolValue("_etext", symTab, &FLASH_used)) return;




}

std::string MemoryMap_T3X::getSymbols()
{
    return string("");
}

void MemoryMap_T3X::print()
{
    string flashUsed = fmtSize(FLASH_used - FLASH_start);
    string flashMax  = fmtSize(FLASH_end - FLASH_start);
    string flashPerc = fmtPerc(100.0 * (FLASH_used - FLASH_start) / (FLASH_end - FLASH_start));
    string ramUsed   = fmtSize(RAM_used - RAM_start);
    string ramMax    = fmtSize(RAM_end - RAM_start);
    string ramPerc   = fmtPerc(100.0 * (RAM_used - RAM_start) / (RAM_end - RAM_start));
    string stackAv   = fmtSize(RAM_end - RAM_used);

    char_table table;
    table << "MEMORY USAGE    "<< endr;
    table << "FLASH: "          << flashUsed << " (" << flashPerc << "of" << flashMax << ")" << endr;
    table << "RAM: "            << ramUsed   << " (" << ramPerc   << "of" << ramMax   << ")" << endr;
    table << "STACK/HEAP: "     << stackAv   << " (available)"    <<  endr;


    // table format --------------------------------------------------------------------------------------
    ft_border_style simple{
        {"", "", "",  // top sep bot (border)
         "", "", ""}, // side in out
        {"", "-", "", // top sep bot (header)
         "", "", ""}, // side in out
         ""};

    table.set_border_style(&simple);
    table.set_cell_text_align(text_align::right);       // all cells right align
    table.set_cell_right_padding(0);                    // left padding is sufficient since we don't have seperators

    table.row(0).set_cell_row_type(row_type::header);   // define header row, span all columns, right padded
    table.cell(0, 0).set_cell_span(6);
    table.cell(0, 0).set_cell_text_align(text_align::right);

    table.cell(3, 2).set_cell_span(4);
    table.cell(3, 2).set_cell_text_align(text_align::left);

    table.column(3).set_cell_left_padding(0);           // no need for left padding before the parantheses
    table.column(6).set_cell_left_padding(0);

    printf("%s\n", table.c_str());

    fmt::print("Functions:");
    int i = 0;
    int totalF = 0;
    for(Symbol& s : functions)
    {
        fmt::print("{:>4} {:>8} {}\n", i, fmtSize(s.size), s.name);
        totalF += s.size;
        i++;
        if (i >= 1500) break;
    }

    fmt::print(fmtSize(totalF));

    fmt::print("\n\nVariables:\n");
    i = 0;
    for(Symbol& s : variables)
    {
        fmt::print("{:>4} {:>8} {}\n",i, fmtSize(s.size), s.name);
        i++;
        if (i >= 1500) break;
    }

    file:///C:/Users/lutz/source/Teensy/tttest/.vsteensy/build/n.lst
    




}