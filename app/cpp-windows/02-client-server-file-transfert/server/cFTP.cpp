#include "cFTP.h"
#include "cFile.h"
#include "cString.h"
#include <iostream>

// output
static const std::string DEF_OUTPUT_PATH = "../../data/output";

// request
static const int DEF_REQUEST_LIMIT_SIZE = 100;
static const std::string DEF_REQUEST_DATA_SEP = ";";

cFTP::cFTP()
{
}

cFTP::~cFTP()
{
}

bool cFTP::saveFile(const std::string &_request, sFTP &_sFTP)
{
    if (!deserialize(_request, _sFTP))
    {
        std::cout << "La deserialisation des donnees du fichier a echoue."
                  << "|request=" << cString(_request).limit(DEF_REQUEST_LIMIT_SIZE).oneLine()
                  << std::endl;
        return false;
    }

    if (!cFile(DEF_OUTPUT_PATH).createDirectory())
    {
        std::cout << "La creation du fichier de sortie a echoue."
                  << "|request=" << cString(_request).limit(DEF_REQUEST_LIMIT_SIZE).oneLine()
                  << std::endl;
        return false;
    }

    std::string oFilename = DEF_OUTPUT_PATH + "/" + _sFTP.filename;
    cFile oFile(oFilename);
    oFile.writeBin(_sFTP.data);

    return true;
}

bool cFTP::deserialize(const std::string &_request, sFTP &_sFTP)
{
    // path
    size_t oPathStart = 0;
    size_t oPathEnd = _request.find(DEF_REQUEST_DATA_SEP, oPathStart);
    if (oPathEnd == std::string::npos)
    {
        std::cout << "Le chemin du fichier est inconnu."
                  << "|request=" << cString(_request).limit(DEF_REQUEST_LIMIT_SIZE).oneLine()
                  << std::endl;
        return false;
    }
    _sFTP.path = _request.substr(oPathStart, oPathEnd - oPathStart);

    // filename
    size_t oFilenameStart = oPathEnd + DEF_REQUEST_DATA_SEP.size();
    size_t oFilenameEnd = _request.find(DEF_REQUEST_DATA_SEP, oFilenameStart);
    if (oFilenameEnd == std::string::npos)
    {
        std::cout << "Le nom du fichier est inconnu."
                  << "|request=" << cString(_request).limit(DEF_REQUEST_LIMIT_SIZE).oneLine()
                  << std::endl;
        return false;
    }
    _sFTP.filename = _request.substr(oFilenameStart, oFilenameEnd - oFilenameStart);

    // size
    size_t oSizeStart = oFilenameEnd + DEF_REQUEST_DATA_SEP.size();
    size_t oSizeEnd = _request.find(DEF_REQUEST_DATA_SEP, oSizeStart);
    if (oSizeEnd == std::string::npos)
    {
        std::cout << "La taille du fichier est inconnu."
                  << "|request=" << cString(_request).limit(DEF_REQUEST_LIMIT_SIZE).oneLine()
                  << std::endl;
        return false;
    }
    std::string oSize = _request.substr(oSizeStart, oSizeEnd - oSizeStart);
    if (!cString(oSize).toInt(_sFTP.size))
    {
        std::cout << "Le format de la taille du fichier est incorrect."
                  << "|size=" << cString(oSize).limit(DEF_REQUEST_LIMIT_SIZE).oneLine()
                  << std::endl;
        return false;
    }

    // data
    size_t oDataStart = oSizeEnd + DEF_REQUEST_DATA_SEP.size();
    _sFTP.data = _request.substr(oDataStart);

    return true;
}
