#include "cSymbol.h"

#include <string>

cSymbol::cSymbol(std::string name)
{
    m_id = ++nextId;
    m_name = name;
}

std::string cSymbol::ToString()
{
    string result("<sym id=\"");
    result += std::to_string(m_id);
    result += "\" name=\"" + m_name + "\" />";

    return result;
}

std::string cSymbol::GetName()
{
    return m_name;
}
