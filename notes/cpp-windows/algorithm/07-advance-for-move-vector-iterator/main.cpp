#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:" << oString << std::endl;

    auto oDistance = [oString](int size = 0)
    {
        std::string::const_iterator it = oString.begin();
        std::advance(it, size);
        return std::distance(it, oString.end());
    };

    std::cout << "[Info]:oDistance()=" << oDistance() << std::endl;
    std::cout << "[Info]:oDistance()=" << oDistance(5) << std::endl;
    return 0;
}
