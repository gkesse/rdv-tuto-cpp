#include <iostream>

int main(int _argc, char **_argv)
{
    try
    {
        std::terminate();
        std::cout << "[Info]:Bonjour tout le monde." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "[Error]:Un probleme a ete rencontre."
                  << "|error=" << e.what()
                  << std::endl;
    }
    std::cout << "[Info]:Fin du programme." << std::endl;
    return 0;
}
