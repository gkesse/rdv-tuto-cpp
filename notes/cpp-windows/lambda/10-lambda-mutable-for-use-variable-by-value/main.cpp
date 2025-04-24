#include <iostream>

int main(int _argc, char **_argv)
{
    int oX;
    int oY = 25;
    auto oAdd = [=, &oX](int a, int b) mutable -> void
    {
        oY += b;
        oX = a + oY;
    };
    oAdd(5, 15);
    std::cout << "[Info]:oAdd(5, 15)=" << oX << std::endl;
    std::cout << "[Info]:oX=" << oX << std::endl;
    std::cout << "[Info]:oY=" << oY << std::endl;
    return 0;
}
