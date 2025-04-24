#pragma once

#include <string>

class cString : public std::string
{
public:
    cString(const std::string &_data);
    ~cString() = default;
    std::string toLower() const;
};
