#pragma once

#include "Symbol.h"
#include <string>
#include <vector>
#include "fort.hpp"



class MemoryMap
{
 public:
    static MemoryMap* MakeMemoryMap(std::string elfFile);
    virtual void print() = 0;
    virtual std::string getSymbols() = 0;

 protected:
    static const Symbol* getSymbol(const std::string& name, const SymTab&);
    static bool getSymbolValue(const std::string& name, const SymTab&, uint32_t* value);

    static SymTab functions;
    static SymTab variables;
    static SymTab constants;

 private:
    static SymTab parse(std::string elfFile);
};