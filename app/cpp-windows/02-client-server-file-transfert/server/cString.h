#pragma once

#include <string>

class cString : public std::string
{
public:
    cString(const std::string &_data);
    ~cString();
    cString limit(int _size) const;
    cString oneLine() const;
    bool toInt(int &_data, int _defaultValue = 0) const;
    bool toInt(size_t &_data, size_t _defaultValue = 0) const;
};
