#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:" << oString << std::endl;

    auto isContain = [oString](char c) -> bool
    {
        return std::any_of(oString.begin(), oString.end(), [c](char a)
                           { return (a == c); });
    };

    std::cout << "[Info]:isContain(e)=" << isContain('e') << std::endl;
    std::cout << "[Info]:isContain(z)=" << isContain('z') << std::endl;
    return 0;
}
