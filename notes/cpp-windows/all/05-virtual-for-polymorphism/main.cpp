#include <iostream>

class cClassA
{
public:
    cClassA() = default;
    virtual ~cClassA() = default;
    virtual void print() const { std::cout << "[Info]:Je suis une classe A." << std::endl; }
};

class cClassB : public cClassA
{
public:
    cClassB() = default;
    ~cClassB() = default;
    void print() const { std::cout << "[Info]:Je suis une classe B." << std::endl; }
};

int main(int _argc, char **_argv)
{
    {
        cClassA &oClass = cClassA();
        oClass.print();
    }
    {
        cClassA &oClass = cClassB();
        oClass.print();
    }
    return 0;
}
