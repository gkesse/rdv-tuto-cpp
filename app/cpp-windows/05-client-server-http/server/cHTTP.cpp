#include "cHTTP.h"
#include <format>
#include <sstream>

static const std::string DEF_HTTP_VERSION_1_1 = "HTTP/1.1";
static const int DEF_HTTP_STATUS_OK = 200;
static const std::string DEF_HTTP_REASON_OK = "OK";
static const std::string DEF_HTTP_CONNECTION_CLOSE = "Close";
static const std::string DEF_HTTP_CONTENT_TYPE_HTML = "text/html; charset=UTF-8";

cHTTP::cHTTP()
{
}

cHTTP::~cHTTP()
{
}

std::string cHTTP::getResponse(const std::string &_content) const
{

    sResponse oResponse = initResponse(_content);
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

cHTTP::sResponse cHTTP::initResponse(const std::string &_content) const
{
    sResponse oResponse;
    oResponse.version = DEF_HTTP_VERSION_1_1;
    oResponse.status = DEF_HTTP_STATUS_OK;
    oResponse.reason = DEF_HTTP_REASON_OK;
    oResponse.connection = DEF_HTTP_CONNECTION_CLOSE;
    oResponse.contentType = DEF_HTTP_CONTENT_TYPE_HTML;
    oResponse.contentLength = (int)_content.size();
    oResponse.contentText = _content;
    return oResponse;
}
