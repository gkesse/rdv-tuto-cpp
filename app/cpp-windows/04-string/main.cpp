#include "cString.h"
#include <iostream>

int main(int _argc, char **_argv)
{
    std::cout << "cString(Bonjour tout le monde.)=" << cString("Bonjour tout le monde.") << std::endl;
    std::cout << "cString(Bonjour tout le monde.).limit(15)=" << cString("Bonjour tout le monde.").limit(15) << std::endl;
    std::cout << "cString(Bonjour tout le monde.\\nBienvenue dans ce tutoriel.).oneLine()=" << std::endl
              << cString("Bonjour tout le monde.\nBienvenue dans ce tutoriel.").oneLine() << std::endl;
    std::cout << "cString(Bonjour tout le monde.\\nBienvenue dans ce tutoriel.).oneLine(40)=" << std::endl
              << cString("Bonjour tout le monde.\nBienvenue dans ce tutoriel.").oneLine(40) << std::endl;
    std::cout << "cString(Bonjour tout le monde.\\nBienvenue dans ce tutoriel.).escape()=" << std::endl
              << cString("Bonjour tout le monde.\nBienvenue dans ce tutoriel.").escape() << std::endl;
    std::cout << "cString(Bonjour tout le monde.\\nBienvenue dans ce tutoriel.).escape(40)=" << std::endl
              << cString("Bonjour tout le monde.\nBienvenue dans ce tutoriel.").escape(40) << std::endl;
    {
        int oInt;
        std::cout << "cString(1000).toInt()=" << cString("1000").toInt(oInt) << std::endl;
        std::cout << "cString(1000).oInt=" << oInt << std::endl;
    }
    {
        int oInt;
        std::cout << "cString(NO_INT).toInt()=" << cString("NO_INT").toInt(oInt, -1) << std::endl;
        std::cout << "cString(NO_INT).oInt=" << oInt << std::endl;
    }
    return 0;
}
