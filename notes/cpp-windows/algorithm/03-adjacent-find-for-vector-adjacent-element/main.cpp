#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonne journee.");
    std::cout << "[Info]:" << oString << std::endl;
    std::string::iterator it = oString.begin();
    for (;;)
    {
        it = std::adjacent_find(it, oString.end(), [](char a, char b)
                                { return a == b; });
        if (it == oString.end())
            break;

        std::cout << "[Info]:" << *it << std::endl;

        it++;
    }
    return 0;
}
