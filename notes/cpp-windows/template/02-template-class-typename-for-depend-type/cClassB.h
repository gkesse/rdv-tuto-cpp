#pragma once

#include <iostream>

class cClassB
{
public:
    cClassB() {}
    ~cClassB() {}
    void print() const { std::cout << "[Info]:Je suis une classe B." << std::endl; }
};
