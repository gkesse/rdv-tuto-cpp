#include "cString.h"
#include <sstream>
#include <algorithm>

cString::cString(const std::string &_data)
    : std::string(_data)
{
}

std::string cString::toCapitalize() const
{
    cString oData(*this);

    std::transform(oData.begin(), oData.end(), oData.begin(), [](char a)
                   { return std::tolower(a); });

    std::stringstream oStream(oData);
    std::string oWord;
    std::string oResult;
    const std::string SPACE = " ";

    while (oStream >> oWord)
    {
        if (!oResult.empty())
            oResult += SPACE;

        oWord[0] = std::toupper(oWord[0]);
        oResult += oWord;
    }

    return oResult;
}
