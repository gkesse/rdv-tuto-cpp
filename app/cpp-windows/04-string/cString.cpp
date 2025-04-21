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
    std::replace(oData.begin(), oData.end(), '\a', ' ');
    std::replace(oData.begin(), oData.end(), '\b', ' ');
    std::replace(oData.begin(), oData.end(), '\f', ' ');
    std::replace(oData.begin(), oData.end(), '\n', ' ');
    std::replace(oData.begin(), oData.end(), '\r', ' ');
    std::replace(oData.begin(), oData.end(), '\t', ' ');
    std::replace(oData.begin(), oData.end(), '\v', ' ');
    return oData;
}

cString cString::oneLine(int _size) const
{
    return limit(_size).oneLine();
}

cString cString::escape() const
{
    std::string oData;
    oData.reserve(size());
    for (const char oChar : *this)
    {
        switch (oChar)
        {
        case '\a':
            oData += "\\a";
            break;
        case '\b':
            oData += "\\b";
            break;
        case '\f':
            oData += "\\f";
            break;
        case '\n':
            oData += "\\n";
            break;
        case '\r':
            oData += "\\r";
            break;
        case '\t':
            oData += "\\t";
            break;
        case '\v':
            oData += "\\v";
            break;
        default:
            oData += oChar;
            break;
        }
    }

    return oData;
}

cString cString::escape(int _size) const
{
    return limit(_size).escape();
}

bool cString::toInt(int &_data, int _defaultValue) const
{
    try
    {
        _data = std::stoi(*this);
        return true;
    }
    catch (...)
    {
        _data = _defaultValue;
    }

    return false;
}

bool cString::toInt(size_t &_data, size_t _defaultValue) const
{
    try
    {
        _data = std::stoi(*this);
        return true;
    }
    catch (...)
    {
        _data = _defaultValue;
    }

    return false;
}
