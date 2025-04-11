#include "cClient.h"
#include <iostream>

int main(int _argc, char **_argv)
{
    cClient oClient(_argc, _argv);

    std::string oRequest("Bonjour tout le monde");
    std::string oResponse;

    if (oClient.run(oRequest, oResponse))
    {
        std::cout << "[Client] : " << oRequest << std::endl;
        std::cout << "[Server] : " << oResponse << std::endl;
    }

    return 0;
}