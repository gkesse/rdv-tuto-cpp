#include <iostream>

class cClassA
{
public:
    cClassA() {}
    ~cClassA() = default;
    void print() const { std::cout << "[Info]:Je suis une classe A." << std::endl; }
};

int main(int _argc, char **_argv)
{
    cClassA oClassA;
    oClassA.print();
    return 0;
}
