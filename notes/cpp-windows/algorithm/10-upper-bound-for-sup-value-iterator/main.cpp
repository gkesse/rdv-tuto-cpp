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

    auto oUpperBound = [](const std::string &_data, char c)
    {
        auto oUp = std::upper_bound(_data.begin(), _data.end(), c, [](char a, char c)
                                    { return (a < c); });
        return (oUp - _data.begin());
    };

    std::cout << "[Info]:oSort(s)=" << oSort(oString) << std::endl;
    std::cout << "[Info]:oUpperBound(s, o)=" << oUpperBound(oSort(oString), 'o') << std::endl;
    std::cout << "[Info]:oUpperBound(s, p)=" << oUpperBound(oSort(oString), 'p') << std::endl;
    std::cout << "[Info]:oUpperBound(s, r)=" << oUpperBound(oSort(oString), 'r') << std::endl;
    return 0;
}
