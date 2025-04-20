#include "cString.h"
#include <algorithm>

static const std::string DEF_STRING_LIMIT_TEXT = "...";

cString::cString(const std::string &_data)
    : std::string(_data)
{
}

cString::~cString()
{
}

cString cString::limit(int _size) const
{
    std::string oData = substr(0, _size);
    if (size() > _size)
    {
        oData += DEF_STRING_LIMIT_TEXT;
    }
    return oData;
}

cString cString::oneLine() const
{
    std::string oData(*this);
    std::replace(oData.begin(), oData.end(), '\r', ' ');
    std::replace(oData.begin(), oData.end(), '\n', ' ');
    std::replace(oData.begin(), oData.end(), '\v', ' ');
    return oData;
}
