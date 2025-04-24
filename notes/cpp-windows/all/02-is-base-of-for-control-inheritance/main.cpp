#include <iostream>

class cClassA
{
public:
    cClassA() {}
    ~cClassA() {}
    void print() const { std::cout << "[Info]:Je suis une classe A." << std::endl; }
};

class cClassB : public cClassA
{
public:
    cClassB() {}
    ~cClassB() {}
    void print() const { std::cout << "[Info]:Je suis une classe B." << std::endl; }
};

int main(int _argc, char **_argv)
{
    // std::is_base_of_v<Base, Derived>
    std::cout << "[Info]:is_base_of_v<A,A>=" << std::is_base_of_v<cClassA, cClassA> << std::endl;
    std::cout << "[Info]:is_base_of_v<B,B>=" << std::is_base_of_v<cClassB, cClassB> << std::endl;
    std::cout << "[Info]:is_base_of_v<A,B>=" << std::is_base_of_v<cClassA, cClassB> << std::endl;
    std::cout << "[Info]:is_base_of_v<B,A>=" << std::is_base_of_v<cClassB, cClassA> << std::endl;
    return 0;
}
