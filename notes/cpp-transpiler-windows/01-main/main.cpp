#include "itranspiler_renderer.h"
#include <iostream>
#include <filesystem>
#include <cmdlime/commandlinereader.h>
#include <sfun/contract.h>
#include <sfun/functional.h>

namespace fs = std::filesystem;

struct HeaderOnlyResultModeCfg : public cmdlime::Config
{
    CMDLIME_ARG(input, fs::path) << "fichier .htcpp à transpiler";
    CMDLIME_PARAM(outputDir, fs::path)() << "répertoire de sortie\n(si vide, le répertoire de travail courant est utilisé)";
    CMDLIME_PARAM(className, std::string)() << "nom de classe généré\n(si vide, le nom du fichier d'entrée est utilisé)";
};

struct SharedLibrarySourceResultModeCfg : public cmdlime::Config
{
    CMDLIME_ARG(input, fs::path) << "fichier .htcpp à transpiler";
    CMDLIME_PARAM(outputDir, fs::path)() << "répertoire de sortie\n(si vide, le répertoire de travail courant est utilisé)";
};

struct HeaderAndSourceResultModeCfg : public cmdlime::Config
{
    CMDLIME_ARG(input, fs::path) << "fichier .htcpp à transpiler";
    CMDLIME_PARAM(outputDir, fs::path)() << "répertoire de sortie\n(si vide, le répertoire de travail actuel est utilisé)";
    CMDLIME_PARAM(className, std::string)() << "nom de la classe générée\n(si vide, le nom du fichier d'entrée est utilisé)";
    CMDLIME_PARAM(configClassName, std::string) << "nom de la classe de configuration";
};

struct Cfg : public cmdlime::Config
{
    CMDLIME_COMMAND(generateHeaderOnly, HeaderOnlyResultModeCfg) << "générer le fichier d'en-tête uniquement";
    CMDLIME_COMMAND(generateSharedLibrarySource, SharedLibrarySourceResultModeCfg) << "générer le fichier source de la bibliothèque partagée";
    CMDLIME_COMMAND(generateHeaderAndSource, HeaderAndSourceResultModeCfg) << "générer les fichiers d'en-tête et source";
};

// functions
static int onRun(const Cfg &cfg);
static std::variant<HeaderOnlyResultModeCfg, SharedLibrarySourceResultModeCfg, HeaderAndSourceResultModeCfg>
getCommand(const Cfg &cfg);
static std::unique_ptr<htcpp::ITranspilerRenderer>
makeTranspilerRenderer(const CommandCfg &cfg);

int main(int _argc, char **_argv)
{
    try
    {
        auto oReader = cmdlime::CommandLineReader<cmdlime::Format::Simple>{"rdvcpp"};
        return oReader.exec<Cfg>(_argc, _argv, onRun);
    }
    catch (const std::exception &e)
    {
        std::cout << "[Error]:Les parametres de l'application sont incorrects."
                  << "|error=" << e.what()
                  << std::endl;
    }

    return 0;
}

static int onRun(const Cfg &cfg)
{
    const auto command = getCommand(cfg);

    return 0;
}

static std::variant<HeaderOnlyResultModeCfg, SharedLibrarySourceResultModeCfg, HeaderAndSourceResultModeCfg>
getCommand(const Cfg &cfg)
{
    sfun::unreachable();
}
