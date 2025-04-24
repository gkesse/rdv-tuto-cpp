#include <iostream>

class cClassA
{
public:
    cClassA() = default;
    virtual ~cClassA() = default;
    void print() const { std::cout << "[Info]:Je suis une classe A." << std::endl; }

    cClassA(const cClassA &) = delete;
    cClassA(cClassA &&) = delete;
    cClassA &operator=(const cClassA &) = delete;
    cClassA &operator=(cClassA &&) = delete;
};

int main(int _argc, char **_argv)
{
    {
        cClassA oClassA;
        oClassA.print();
    }
    {
        // 'cClassA::cClassA(const cClassA &)' :
        // tentative de référencement d'une fonction supprimée
        // cClassA &oClassA = cClassA();
    }
    {
        // 'cClassA::cClassA(cClassA &&)' :
        // tentative de référencement d'une fonction supprimée
        // cClassA oClassA = cClassA();
    }
    return 0;
}
