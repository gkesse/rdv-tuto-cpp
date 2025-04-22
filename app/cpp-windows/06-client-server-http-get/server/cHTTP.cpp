#include "cHTTP.h"
#include "cString.h"
#include <format>
#include <sstream>
#include <iostream>

// http
static const std::string DEF_HTTP_VERSION_1_0 = "HTTP/1.0";
static const std::string DEF_HTTP_VERSION_1_1 = "HTTP/1.1";
static const std::string DEF_HTTP_VERSION_2_0 = "HTTP/2.0";
//
static const std::string DEF_HTTP_CONNECTION_CLOSE = "Close";
//
static const std::string DEF_HTTP_METHOD_GET = "GET";
static const std::string DEF_HTTP_METHOD_POST = "POST";

// request
static const int DEF_REQUEST_LIMIT_SIZE = 100;
static const int DEF_REQUEST_HEADER_SIZE = 256;
static const std::string DEF_REQUEST_SEP_SPACE = " ";
static const std::string DEF_REQUEST_SEP_CRLF = "\r\n";

cHTTP::cHTTP()
{
}

cHTTP::~cHTTP()
{
}

bool cHTTP::analyzeRequestHTTP(sRequest &_requestHTTP, const std::string &_request) const
{
    const std::string oRequestHeader = _request.substr(0, DEF_REQUEST_HEADER_SIZE);

    // method
    size_t oMethodStart = 0;
    size_t oMethodEnd = oRequestHeader.find(DEF_REQUEST_SEP_SPACE, oMethodStart);
    if (oMethodEnd == std::string::npos)
    {
        std::cout << "[Error]:La methode de la requete HTTP n'est pas determinee."
                  << "|request=" << cString(oRequestHeader).escape(DEF_REQUEST_LIMIT_SIZE)
                  << std::endl;
        return false;
    }
    std::string oMethod = oRequestHeader.substr(oMethodStart, oMethodEnd - oMethodStart);
    if (!isMethodAccepted(oMethod))
    {
        std::cout << "[Error]:La methode de la requete HTTP n'est pas supportee."
                  << "|request=" << cString(oRequestHeader).escape(DEF_REQUEST_LIMIT_SIZE)
                  << std::endl;
        return false;
    }

    // uri
    size_t oUriStart = oMethodEnd + DEF_REQUEST_SEP_SPACE.size();
    size_t oUriEnd = oRequestHeader.find(DEF_REQUEST_SEP_SPACE, oUriStart);
    if (oUriEnd == std::string::npos)
    {
        std::cout << "[Error]:L'uri de la requete HTTP n'est pas determinee."
                  << "|request=" << cString(oRequestHeader).escape(DEF_REQUEST_LIMIT_SIZE)
                  << std::endl;
        return false;
    }
    std::string oUri = oRequestHeader.substr(oUriStart, oUriEnd - oUriStart);

    // version
    size_t oVersionStart = oUriEnd + DEF_REQUEST_SEP_SPACE.size();
    size_t oVersionEnd = oRequestHeader.find(DEF_REQUEST_SEP_CRLF, oVersionStart);
    if (oVersionEnd == std::string::npos)
    {
        std::cout << "[Error]:La version de la requete HTTP n'est pas determinee."
                  << "|request=" << cString(oRequestHeader).escape(DEF_REQUEST_LIMIT_SIZE)
                  << std::endl;
        return false;
    }
    std::string oVersion = oRequestHeader.substr(oVersionStart, oVersionEnd - oVersionStart);
    if (!isVersionAccepted(oVersion))
    {
        std::cout << "[Error]:La version de la requete HTTP n'est pas supportee."
                  << "|request=" << cString(oRequestHeader).escape(DEF_REQUEST_LIMIT_SIZE)
                  << std::endl;
        return false;
    }

    _requestHTTP.method = oMethod;
    _requestHTTP.uri = oUri;
    _requestHTTP.version = oVersion;
    return true;
}

std::string cHTTP::getResponse(const std::string &_contentText, const std::string &_contentType, const STATUS_CODE &_statusCode) const
{

    sResponse oResponse = initResponse(_contentText, _contentType, _statusCode);
    std::stringstream oResponseText;

    oResponseText << std::format("{} {} {}\r\n", oResponse.version, oResponse.status, oResponse.reason);
    oResponseText << std::format("Connection: {}\r\n", oResponse.connection);
    oResponseText << std::format("Content-Type: {}\r\n", oResponse.contentType);
    oResponseText << std::format("Content-Length: {}\r\n", oResponse.contentLength);
    oResponseText << "\r\n";
    oResponseText << oResponse.contentText;
    oResponseText << "\r\n";

    return oResponseText.str();
}

bool cHTTP::isGET(const sRequest &_requestHTTP) const
{
    return (_requestHTTP.method == DEF_HTTP_METHOD_GET);
}

bool cHTTP::isPOST(const sRequest &_requestHTTP) const
{
    return (_requestHTTP.method == DEF_HTTP_METHOD_POST);
}

bool cHTTP::isMethodAccepted(const std::string &_methodHTTP) const
{
    if ((_methodHTTP == DEF_HTTP_METHOD_GET) ||
        (_methodHTTP == DEF_HTTP_METHOD_POST))
    {
        return true;
    }
    return false;
}

bool cHTTP::isVersionAccepted(const std::string &_versionHTTP) const
{
    if ((_versionHTTP == DEF_HTTP_VERSION_1_0) ||
        (_versionHTTP == DEF_HTTP_VERSION_1_1) ||
        (_versionHTTP == DEF_HTTP_VERSION_2_0))
    {
        return true;
    }
    return false;
}

cHTTP::sResponse cHTTP::initResponse(const std::string &_contentText, const std::string &_contentType, const STATUS_CODE &_statusCode) const
{
    sResponse oResponse;
    oResponse.version = DEF_HTTP_VERSION_1_1;
    oResponse.status = _statusCode;
    oResponse.reason = HTTP_STATUS_REASON(_statusCode);
    oResponse.connection = DEF_HTTP_CONNECTION_CLOSE;
    oResponse.contentType = _contentType;
    oResponse.contentLength = (int)_contentText.size();
    oResponse.contentText = _contentText;
    return oResponse;
}
