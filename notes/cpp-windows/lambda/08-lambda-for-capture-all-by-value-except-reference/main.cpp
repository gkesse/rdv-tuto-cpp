#include <iostream>

int main(int _argc, char **_argv)
{
    int oX;
    int oY = 25;
    auto oAdd = [=, &oX](int a, int b) -> void
    {
        oX = a + b + oY;
    };
    oAdd(5, 15);
    std::cout << "[Info]:oAdd(5, 15)=" << oX << std::endl;
    return 0;
}
