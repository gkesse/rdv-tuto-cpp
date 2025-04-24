#include "cString.h"
#include <algorithm>

cString::cString(const std::string &_data)
    : std::string(_data)
{
}

std::string cString::toUpper() const
{
    cString oData(*this);
    std::transform(oData.begin(), oData.end(), oData.begin(), [](char a)
                   { return std::toupper(a); });
    return oData;
}
