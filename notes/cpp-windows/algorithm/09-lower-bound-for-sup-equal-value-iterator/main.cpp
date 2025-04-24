#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");
    std::cout << "[Info]:oString=" << oString << std::endl;

    auto oSort = [](const std::string &_data)
    {
        std::string oData(_data);
        std::sort(oData.begin(), oData.end(), [](char a, char b)
                  { return (a < b); });
        return oData;
    };

    auto oLowerBound = [](const std::string &_data, char c)
    {
        auto oLow = std::lower_bound(_data.begin(), _data.end(), c, [](char a, char c)
                                     { return (a < c); });
        return (oLow - _data.begin());
    };

    std::cout << "[Info]:oSort(s)=" << oSort(oString) << std::endl;
    std::cout << "[Info]:oLowerBound(s, o)=" << oLowerBound(oSort(oString), 'o') << std::endl;
    std::cout << "[Info]:oLowerBound(s, p)=" << oLowerBound(oSort(oString), 'p') << std::endl;
    std::cout << "[Info]:oLowerBound(s, r)=" << oLowerBound(oSort(oString), 'r') << std::endl;
    return 0;
}
