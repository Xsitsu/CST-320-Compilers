#include "lex.h"

#include <string>

yylval_t yylval;
cSymbolTable *g_symbolTable;

cSymbol *Insert(const char *name)
{
    std::string to_insert = name;
    return g_symbolTable->Insert(to_insert);
}

void IncreaseScope()
{
    g_symbolTable->IncreaseScope();
}

void DecreaseScope()
{
    g_symbolTable->DecreaseScope();
}
