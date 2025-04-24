#pragma once

#include "cClassA.h"

template <typename ClassType>
class cClassC
{
public:
    typedef typename cClassA<ClassType>::sClassA sClassA;

public:
    cClassC() {}
    ~cClassC() {}
    void print() const { m_sClass.oClass.print(); }

private:
    sClassA m_sClass;
};
