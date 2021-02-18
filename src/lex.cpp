//**************************************
// lex.cpp
// Author: Jacob Locke
//
// Globals functions and variables used by the compiler.
//

#include "lex.h"

#include <string>

cSymbolTable *g_symbolTable;
bool g_semanticErrorHappened;

cSymbol *Insert(const char *text)
{
    std::string name = text;
    cSymbol *symbol = g_symbolTable->FindLocal(name);
    if (!symbol)
    {
        symbol = new cSymbol(name);
        g_symbolTable->Insert(symbol);
    }
    return symbol;
}

void IncreaseScope()
{
    g_symbolTable->IncreaseScope();
}

void DecreaseScope()
{
    g_symbolTable->DecreaseScope();
}
