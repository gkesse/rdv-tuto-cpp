#pragma once

#include <string>

template <typename ClassType>
class cClassA
{
public:
    struct sClassA
    {
        ClassType oClass;
    };

public:
    cClassA() {}
    ~cClassA() {}
    void print() const { m_sClass.oClass.print(); }

private:
    sClassA m_sClass;
};
