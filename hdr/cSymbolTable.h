#pragma once

class cSymbolTable
{
    public:
        // Construct an empty symbol table
        cSymbolTable();

        // Increase the scope: add a level to the nested symbol table
        // Return value is the newly created scope
        symbolTable_t *IncreaseScope();

        // Decrease the scope: remove the outer-most scope.
        // Returned value is the outer-most scope AFTER the pop.
        //
        // NOTE: do NOT clean up memory after poping the table. Parts of the
        // AST will probably contain pointers to symbols in the popped table.
        symbolTable_t *DecreaseScope();

        // insert a symbol into the table
        // Assumes the symbol is not already in the table
        void Insert(cSymbol *sym);

        // Do a lookup in the nested table. 
        // Return the symbol for the outer-most match. 
        // Returns nullptr if no match is found.
        cSymbol *Find(string name);

        // Find a symbol in the outer-most scope.
        // Returns nullptr if the symbol is not found.
        cSymbol *FindLocal(string name);

};

