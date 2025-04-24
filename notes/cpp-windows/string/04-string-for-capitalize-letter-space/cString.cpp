#include "cString.h"

cString::cString(const std::string &_data)
    : std::string(_data)
{
}

std::string cString::toCapitalize() const
{
    cString oData(*this);

    for (int i = 0; i < oData.length(); i++)
    {
        if ((oData[i] != ' ') && (i == 0 || oData[i - 1] == ' '))
        {
            if (oData[i] >= 'a' && oData[i] <= 'z')
            {
                oData[i] = (char)(oData[i] - 'a' + 'A');
            }
        }
        else if (oData[i] >= 'A' && oData[i] <= 'Z')
        {
            oData[i] = (char)(oData[i] + 'a' - 'A');
        }
    }

    return oData;
}
