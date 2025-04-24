#include "cString.h"
#include <iostream>

int main(int _argc, char **_argv)
{
    cString oString("Bonjour   tout   le monde.");
    std::cout << "[Info]:" << oString << std::endl;
    std::cout << "[Info]:" << oString.toCapitalize() << std::endl;
    return 0;
}
