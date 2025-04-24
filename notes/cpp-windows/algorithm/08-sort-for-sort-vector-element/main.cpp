#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:" << oString << std::endl;

    auto oSort = [oString]()
    {
        std::string oData(oString);
        std::sort(oData.begin(), oData.end(), [](char a, char b)
                  { return (a < b); });
        return oData;
    };

    std::cout << "[Info]:" << oSort() << std::endl;
    return 0;
}
