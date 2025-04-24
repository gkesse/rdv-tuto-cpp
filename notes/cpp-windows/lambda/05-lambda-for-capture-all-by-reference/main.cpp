#include <iostream>

int main(int _argc, char **_argv)
{
    int oX;
    auto oAdd = [&](int a, int b) -> void
    {
        oX = a + b;
    };
    oAdd(5, 15);
    std::cout << "[Info]:oAdd(5, 15)=" << oX << std::endl;
    return 0;
}
