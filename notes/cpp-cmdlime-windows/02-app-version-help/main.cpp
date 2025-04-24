#include <iostream>
#include <cmdlime/commandlinereader.h>

struct Cfg : public cmdlime::Config
{
    CMDLIME_ARG(zipCode, int);
    CMDLIME_PARAM(surname, std::string);
    CMDLIME_PARAM(name, std::string)();
    CMDLIME_FLAG(verbose);
};

static int onMain(const Cfg &cfg);

int main(int _argc, char **_argv)
{
    auto reader = cmdlime::CommandLineReader{"rdvcpp"};
    reader.setVersionInfo("rdvcpp 1.0");
    return reader.exec<Cfg>(_argc, _argv, onMain);
}

static int onMain(const Cfg &cfg)
{
    std::cout << "[Info]:Les parametres de l'application sont corrects."
              << "|cfg.surname=" << cfg.surname
              << "|cfg.name=" << cfg.name
              << "|cfg.zipCode=" << cfg.zipCode
              << "|cfg.verbose=" << cfg.verbose
              << std::endl;
    return 0;
}
