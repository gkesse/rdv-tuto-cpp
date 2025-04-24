#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oString("Bonjour tout le monde.");

    auto oCopy = [](const std::string &_data)
    {
        std::string oData(_data.size(), '\0');
        std::copy(_data.begin(), _data.end(), oData.begin());
        return oData;
    };

    std::cout << "[Info]:oString=" << oString << std::endl;
    std::cout << "[Info]:oCopy=" << oCopy(oString) << std::endl;
    return 0;
}
