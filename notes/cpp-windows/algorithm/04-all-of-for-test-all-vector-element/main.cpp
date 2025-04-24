#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:" << oString << std::endl;

    auto noContain = [oString](char c) -> bool
    {
        return std::all_of(oString.begin(), oString.end(), [c](char a)
                           { return (a != c); });
    };

    std::cout << "[Info]:noContain(e)=" << noContain('e') << std::endl;
    std::cout << "[Info]:noContain(z)=" << noContain('z') << std::endl;
    return 0;
}
