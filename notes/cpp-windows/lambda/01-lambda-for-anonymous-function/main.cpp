#include <iostream>

int main(int _argc, char **_argv)
{
    auto oAdd = [](int a, int b)
    {
        return a + b;
    };
    std::cout << "[Info]:oAdd(5, 15)=" << oAdd(5, 15) << std::endl;
    return 0;
}
