//**************************************
// cSymbolTable.cpp
// Author: Jacob Locke
//

#include "cSymbolTable.h"

#include <stdlib.h>
#include <string>

cSymbolTable::cSymbolTable()
{
    this->IncreaseScope(); // Global Scope
    cSymbol *sym1 = new cSymbol("char");
    cSymbol *sym2 = new cSymbol("int");
    cSymbol *sym3 = new cSymbol("float");

    sym1->SetIsType(true);
    sym2->SetIsType(true);
    sym3->SetIsType(true);

    this->Insert(sym1);
    this->Insert(sym2);
    this->Insert(sym3);
}

symbolTable_t *cSymbolTable::IncreaseScope()
{
    symbolTable_t *newScope = new symbolTable_t();
    this->scopes.push_back(newScope);
    return newScope;
}

symbolTable_t *cSymbolTable::DecreaseScope()
{
    if (this->scopes.size() > 1)
    {
        this->scopes.pop_back();
        return this->scopes.back();
    }
    return nullptr;
}

void cSymbolTable::Insert(cSymbol *sym)
{
    if (this->FindLocal(sym->GetName()))
    {
        // Probably should error idk
    }

    this->scopes.back()->emplace(sym->GetName(), sym);
}

cSymbol *cSymbolTable::Find(string name)
{
    cSymbol *find = nullptr;

    std::list<symbolTable_t*>::reverse_iterator itr;
    for (itr = this->scopes.rbegin(); itr != this->scopes.rend(); ++itr)
    {
        find = _FindInScope(*itr, name);
        if (find != nullptr)
            return find;    
    }
    return nullptr;
}

cSymbol *cSymbolTable::FindLocal(string name)
{
    return this->_FindInScope(this->scopes.back(), name);
}

cSymbol *cSymbolTable::_FindInScope(symbolTable_t *scope, string name)
{
    symbolTable_t::iterator got = scope->find(name);
    if (got != scope->end())
    {
        return got->second;
    }
    return nullptr;
}