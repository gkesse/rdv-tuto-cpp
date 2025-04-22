#pragma once

#include "cHttpStatusCode.h"
#include <string>

class cHTTP
{
public:
    struct sRequest
    {
        std::string method;
        std::string uri;
        std::string version;
    };

    struct sResponse
    {
        std::string version;
        int status;
        std::string reason;
        std::string connection;
        std::string contentType;
        int contentLength;
        std::string contentText;
    };

    using STATUS_CODE = HTTP_STATUS_CODE::eValues;

public:
    cHTTP();
    ~cHTTP();
    bool analyzeRequestHTTP(sRequest &_requestHTTP, const std::string &_request) const;
    std::string getResponse(const std::string &_contentText, const std::string &_contentType, const STATUS_CODE &_statusCode) const;
    bool isGET(const sRequest &_requestHTTP) const;
    bool isPOST(const sRequest &_requestHTTP) const;

private:
    bool isMethodAccepted(const std::string &_methodHTTP) const;
    bool isVersionAccepted(const std::string &_versionHTTP) const;
    sResponse initResponse(const std::string &_contentText, const std::string &_contentType, const STATUS_CODE &_statusCode) const;
};
