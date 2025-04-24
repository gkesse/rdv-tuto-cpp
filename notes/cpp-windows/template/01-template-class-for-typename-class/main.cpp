#include <iostream>

class cClassA
{
public:
    cClassA() {}
    ~cClassA() {}
    void print() const { std::cout << "[Info]:Je suis une classe A." << std::endl; }
};

class cClassB
{
public:
    cClassB() {}
    ~cClassB() {}
    void print() const { std::cout << "[Info]:Je suis une classe B." << std::endl; }
};

template <typename ClassType>
class cClassC
{
public:
    cClassC() {}
    ~cClassC() {}
    void print() const { m_class.print(); }

private:
    ClassType m_class;
};

template <class ClassType>
class cClassD
{
public:
    cClassD() {}
    ~cClassD() {}
    void print() const { m_class.print(); }

private:
    ClassType m_class;
};

int main(int _argc, char **_argv)
{
    {
        cClassC<cClassA> oClassA;
        oClassA.print();
        cClassC<cClassB> oClassB;
        oClassB.print();
    }

    {
        cClassD<cClassA> oClassA;
        oClassA.print();
        cClassD<cClassB> oClassB;
        oClassB.print();
    }
    return 0;
}
