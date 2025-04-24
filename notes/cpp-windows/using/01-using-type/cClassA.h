#pragma once

#include <string>

class cClassA
{
public:
    struct sClassA
    {
        std::string arg1;
        std::string arg2;
        std::string arg3;
    };

public:
    cClassA();
    ~cClassA();
    void load(sClassA &_sClassA) const;
    void print(const sClassA &_sClassA) const;
};
