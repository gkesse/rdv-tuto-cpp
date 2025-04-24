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
    // std::is_convertible_v<From, To>
    std::cout << "[Info]:is_convertible_v<A,A>=" << std::is_convertible_v<cClassA, cClassA> << std::endl;
    std::cout << "[Info]:is_convertible_v<A,B>=" << std::is_convertible_v<cClassA, cClassB> << std::endl;
    std::cout << "[Info]:is_convertible_v<B,A>=" << std::is_convertible_v<cClassB, cClassA> << std::endl;
    std::cout << "[Info]:is_convertible_v<A*,A*>=" << std::is_convertible_v<cClassA *, cClassA *> << std::endl;
    std::cout << "[Info]:is_convertible_v<A*,B*>=" << std::is_convertible_v<cClassA *, cClassB *> << std::endl;
    std::cout << "[Info]:is_convertible_v<B*,A*>=" << std::is_convertible_v<cClassB *, cClassA *> << std::endl;
    return 0;
}
