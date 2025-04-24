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

    auto oBinarySearch = [](const std::string &_data, char c)
    {
        return std::binary_search(_data.begin(), _data.end(), c, [](char a, char c)
                                  { return (a < c); });
    };

    std::cout << "[Info]:oSort(s)=" << oSort(oString) << std::endl;
    std::cout << "[Info]:oBinarySearch(s, o)=" << oBinarySearch(oSort(oString), 'o') << std::endl;
    std::cout << "[Info]:oBinarySearch(s, p)=" << oBinarySearch(oSort(oString), 'p') << std::endl;
    std::cout << "[Info]:oBinarySearch(s, r)=" << oBinarySearch(oSort(oString), 'r') << std::endl;
    return 0;
}
