#include "cClient.h"
#include "cFile.h"
#include <iostream>

static const std::string DEF_INPUT_FILENAME = "../../data/input/input.txt";

int main(int _argc, char **_argv)
{
    cClient oClient(_argc, _argv);

    cFile oFile(DEF_INPUT_FILENAME);
    std::string oRequest;

    if (oFile.exitsFile())
    {
        oRequest = oFile.readBin();
    }
    else
    {
        oRequest = "Erreur lors du chargement du fichier";
    }

    std::string oResponse;

    if (oClient.run(oRequest, oResponse))
    {
        std::cout << "[Client] : DEF_INPUT_FILENAME=" << DEF_INPUT_FILENAME << std::endl;
        std::cout << "[Server] : " << oResponse << std::endl;
    }

    return 0;
}
