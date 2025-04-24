#include "cClassA.h"
#include <iostream>

cClassA::cClassA()
{
}

cClassA::~cClassA()
{
}

void cClassA::load(sClassA &_sClassA) const
{
    _sClassA.arg1 = "ARG1";
    _sClassA.arg2 = "ARG2";
    _sClassA.arg3 = "ARG3";
}

void cClassA::print(const sClassA &_sClassA) const
{
    std::cout << "[Info]:Je suis une classe A."
              << "|arg1=" << _sClassA.arg1
              << "|arg2=" << _sClassA.arg2
              << "|arg3=" << _sClassA.arg3
              << std::endl;
}
