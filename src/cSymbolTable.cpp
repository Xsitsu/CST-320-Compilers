#include "cSymbolTable.h"

#include <string>

cSymbolTable::cSymbolTable()
{

}

symbolTable_t *cSymbolTable::IncreaseScope()
{
    symbolTable_t *newScope = new symbolTable_t();
    this->scopes.append(newScope);
    return newScope;
}

symbolTable_t *cSymbolTable::DecreaseScope()
{
    if (this->scopes.size() > 1)
    {
        this->scopes.pop_back();
        return this->scopes.back();
    }
    return null;
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
    cSymbol *find = null;

    std::list<symbolTable_t*>::reverse_iterator itr;
    for (itr = this->scopes.rbegin(); itr != this->scopes.rend(); ++itr)
    {
        find = _FindInScope(*itr, name);
        if (find != null)
            return find;    
    }
    return null;
}

cSymbol *cSymbolTable::FindLocal(string name)
{
    return this->_FindInScope(this->scopes.back(), name);
}

cSymbol *cSymbolTable::_FindInScope(symbolTable_t *scope, string name)
{
    symbolTable_t::iterator got = scope->Find(name);
    if (got != scope->end())
    {
        return got.second;
    }
    return null;
}