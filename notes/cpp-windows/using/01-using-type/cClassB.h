#pragma once

#include "cClassA.h"

class cClassB
{
public:
    using sClassA = cClassA::sClassA;

public:
    cClassB();
    ~cClassB();
    void print() const;

private:
    sClassA m_sClassA;
};
