#include "cFTP.h"
#include "cFile.h"
#include "cClient.h"
#include "cString.h"
#include <iostream>

// request
static const int DEF_REQUEST_LIMIT_SIZE = 100;
static const std::string DEF_REQUEST_DATA_SEP = ";";

cFTP::cFTP()
{
}

cFTP::~cFTP()
{
}

void cFTP::sendFile(const std::string &_filename)
{
    sFTP oFTP;
    std::string oRequest;

    if (loadFile(_filename, oFTP))
    {
        oRequest = serialize(oFTP);
    }
    else
    {
        oRequest = "Erreur lors du chargement du fichier";
    }

    cClient oClient;
    std::string oResponse;

    if (oClient.run(oRequest, oResponse))
    {
        std::cout << "[Client] : ================================" << std::endl;
        std::cout << "[Client] : oRequest=" << cString(oRequest).limit(DEF_REQUEST_LIMIT_SIZE).oneLine() << std::endl;
        std::cout << "[Server] : " << oResponse << std::endl;
    }
}

bool cFTP::loadFile(const std::string &_filename, sFTP &_sFTP)
{
    cFile oFile(_filename);

    if (!oFile.exitsFile())
    {
        std::cout << "Le fichier n'existe pas."
                  << "|filename=" << _filename
                  << std::endl;
        return false;
    }

    _sFTP.path = _filename;
    _sFTP.filename = oFile.getFilename();
    _sFTP.data = oFile.readBin();
    _sFTP.size = _sFTP.data.size();
    return true;
}

std::string cFTP::serialize(const sFTP &_sFTP)
{
    std::string oData;
    oData += _sFTP.path + DEF_REQUEST_DATA_SEP;
    oData += _sFTP.filename + DEF_REQUEST_DATA_SEP;
    oData += std::to_string(_sFTP.size) + DEF_REQUEST_DATA_SEP;
    oData.append(&_sFTP.data[0], _sFTP.size);
    return oData;
}
