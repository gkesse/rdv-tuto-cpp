#include "cClassB.h"
#include "cClassA.h"
#include <iostream>

cClassB::cClassB()
{
    cClassA oClassA;
    oClassA.load(m_sClassA);
}

cClassB::~cClassB()
{
}

void cClassB::print() const
{
    std::cout << "[Info]:Je suis une classe B." << std::endl;
    cClassA oClassA;
    oClassA.print(m_sClassA);
}
