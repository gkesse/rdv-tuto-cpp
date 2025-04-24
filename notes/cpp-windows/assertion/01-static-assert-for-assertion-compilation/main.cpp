#include <type_traits>
#include <iostream>

int main(int _argc, char **_argv)
{
    // static_assert(false, "[Error]:Je leve une assertion a la compilation.");
    static_assert(true, "[Error]:Je leve une assertion a la compilation.");
    std::cout << "[Info]:Bonjour tout le monde." << std::endl;
    return 0;
}
