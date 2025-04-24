#include <iostream>

class cAdd
{
public:
    cAdd() = default;
    ~cAdd() = default;
    int operator()(int a, int b) const { return a + b; }
};

int main(int _argc, char **_argv)
{
    cAdd oAdd;
    std::cout << "[Info]:oAdd(5, 15)=" << oAdd(5, 15) << std::endl;
    return 0;
}
