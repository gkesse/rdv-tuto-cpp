#include <iostream>
#include <algorithm>

int main(int _argc, char **_argv)
{
    std::string oDataA("DATA_A");
    std::string oDataB("DATA_B");

    std::cout << "[Info]oDataA=" << oDataA << std::endl;
    std::cout << "[Info]oDataB=" << oDataB << std::endl;

    std::swap(oDataA, oDataB);

    std::cout << "[Info]oDataA=" << oDataA << std::endl;
    std::cout << "[Info]oDataB=" << oDataB << std::endl;
    return 0;
}
