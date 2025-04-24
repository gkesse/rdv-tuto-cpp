#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:" << oString << std::endl;

    auto oDistance = [oString]()
    {
        return std::distance(oString.begin(), oString.end());
    };

    std::cout << "[Info]:oDistance()=" << oDistance() << std::endl;
    return 0;
}
