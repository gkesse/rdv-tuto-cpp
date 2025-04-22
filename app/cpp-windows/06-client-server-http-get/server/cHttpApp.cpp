#include "cHttpApp.h"
#include "cHttpGet.h"

cHttpApp::cHttpApp()
{
}

cHttpApp::~cHttpApp()
{
}

void cHttpApp::run(const sRequest &_requestHTTP, std::string &_responseText, std::string &_contentType, STATUS_CODE &_statusCode) const
{
    cHTTP oHTTP;
    if (oHTTP.isGET(_requestHTTP))
    {
        cHttpGet oGet;
        oGet.run(_requestHTTP, _responseText, _contentType, _statusCode);
    }
    else if (oHTTP.isPOST(_requestHTTP))
    {
        _responseText = "<h1>Bonjour tout le monde POST</h1>";
    }
    else
    {
        _responseText = "Un problème a été rencontré.";
    }
}
