#include <iostream>
#include <cmdlime/commandlinereader.h>

struct Cfg : public cmdlime::Config
{
    CMDLIME_ARG(zipCode, int);
    CMDLIME_PARAM(name, std::string);
    CMDLIME_FLAG(verbose);
};

int main(int _argc, char **_argv)
{
    try
    {
        auto reader = cmdlime::CommandLineReader{"rdvcpp"};
        auto cfg = reader.read<Cfg>(_argc, _argv);
        std::cout << "[Info]:Les parametres de l'application sont corrects."
                  << "|cfg.name=" << cfg.name
                  << "|cfg.zipCode=" << cfg.zipCode
                  << "|cfg.verbose=" << cfg.verbose
                  << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "[Error]:Les parametres de l'application sont incorrects."
                  << "|error=" << e.what()
                  << std::endl;
    }

    return 0;
}
