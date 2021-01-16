#include "lex.h"

#include <string>

yylval_t yylval;
cSymbolTable *g_symbolTable;

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
