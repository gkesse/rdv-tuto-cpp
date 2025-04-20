#pragma once

#include <string>

class cString : public std::string
{
public:
    cString(const std::string &_data);
    ~cString();
    cString limit(int _size) const;
    cString oneLine() const;
};
