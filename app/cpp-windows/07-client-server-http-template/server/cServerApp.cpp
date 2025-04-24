#include "cServerApp.h"
#include "cHTTP.h"
#include "cHttpApp.h"

// http
static const std::string DEF_HTTP_CONTENT_TYPE_HTML = "text/html; charset=UTF-8";

cServerApp::cServerApp()
{
}

cServerApp::~cServerApp()
{
}

void cServerApp::run(const std::string &_request, std::string &_response) const
{
    cHTTP oHTTP;
    cHTTP::sRequest oRequestHTTP;

    if (oHTTP.analyzeRequestHTTP(oRequestHTTP, _request))
    {
        cHttpApp oApp;
        std::string oResponse;
        cHTTP::STATUS_CODE oStatusCode = HTTP_STATUS_CODE::OK_200;
        std::string oContentType = DEF_HTTP_CONTENT_TYPE_HTML;

        oApp.run(oRequestHTTP, oResponse, oContentType, oStatusCode);
        _response = oHTTP.getResponse(oResponse, oContentType, oStatusCode);
    }
    else
    {
        _response = "Un probleme a ete rencontre.";
    }
}
