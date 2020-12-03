#pragma once

#include <string>
#include <vector>

struct Symbol
{
    Symbol(std::string name, uint32_t value, uint32_t size, char type, char bind, std::string section)
    {
        this->name = name;
        this->value = value;
        this->size = size;
        this->type = type;
        this->section = section;
        this->bind = bind;
    }

    std::string name;
    std::string file;
    uint32_t value;
    uint32_t size;
    char type;
    char bind;
    std::string section;
};

using SymTab = std::vector<Symbol>;
