#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:" << oString << std::endl;
    std::transform(oString.begin(), oString.end(), oString.begin(), [](char a)
                   { return a + 1; });
    std::cout << "[Info]:" << oString << std::endl;
    return 0;
}
