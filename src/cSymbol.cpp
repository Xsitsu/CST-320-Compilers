//**************************************
// cSymbol.cpp
// Author: Jacob Locke
//

#include "cSymbol.h"

#include <string>

long long cSymbol::nextId = 0;

cSymbol::cSymbol(std::string name)  : cAstNode()
{
    m_id = ++nextId;
    m_name = name;
}

std::string cSymbol::GetName()
{
    return m_name;
}

bool cSymbol::IsType()
{
    return m_isType;
}

void cSymbol::SetIsType(bool val)
{
    m_isType = val;
}

string cSymbol::AttributesToString()
{
    string result(" id=\"");
    result += std::to_string(m_id);
    result += "\" name=\"" + m_name + "\"";
    return result;
}

string cSymbol::NodeType()
{
    return string("sym");
}

void cSymbol::Visit(cVisitor *visitor)
{
    visitor->Visit(this);
}