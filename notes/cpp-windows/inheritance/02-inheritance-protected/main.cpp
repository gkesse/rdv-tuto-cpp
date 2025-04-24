#include <iostream>

class cClassA
{
public:
    cClassA() {}
    ~cClassA() {}
    void printA() const { std::cout << "[Info]:Je suis une classe A." << std::endl; }
};

class cClassB : protected cClassA
{
public:
    cClassB() {}
    ~cClassB() {}
    void printB() const { std::cout << "[Info]:Je suis une classe B." << std::endl; }
};

class cClassC : public cClassB
{
public:
    cClassC() {}
    ~cClassC() {}
    void printC() const { std::cout << "[Info]:Je suis une classe C." << std::endl; }
};

int main(int _argc, char **_argv)
{
    std::cout << "===[cClassA]===" << std::endl;
    cClassA oClassA;
    oClassA.printA();

    std::cout << "===[cClassB]===" << std::endl;
    cClassB oClassB;
    // oClassB.printA();
    oClassB.printB();

    std::cout << "===[cClassC]===" << std::endl;
    cClassC oClassC;
    // oClassC.printA();
    oClassC.printB();
    oClassC.printC();
    return 0;
}
