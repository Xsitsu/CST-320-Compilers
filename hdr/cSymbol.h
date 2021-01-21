#pragma once
//********************************************************
// cSymbol.h - Define a class for symbols
//
// Author: Philip Howard
//
#include <string>

using std::string;

class cSymbol
{
    public:
        // Construct a symbol given its name
        cSymbol(string name);

        // Return a string representation of a symbol
        // Return value is an XML node
        string ToString();

        // Return name of symbol
        string GetName();

    protected:
        static long long nextId;    // keeps track of unique symbol IDs
        long long m_id;             // Unique ID for this symbol
        string m_name;              // Symbol name
};
