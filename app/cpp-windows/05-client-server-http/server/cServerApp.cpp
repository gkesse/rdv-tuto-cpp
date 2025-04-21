#include "cServerApp.h"
#include "cHTTP.h"

cServerApp::cServerApp()
{
}

cServerApp::~cServerApp()
{
}

void cServerApp::run(const std::string &_request, std::string &_response)
{
    cHTTP oHTTP;
    _response = oHTTP.getResponse("<h1>Bonjour tout le monde.</h1>");
}
