#pragma once

#include <string>

class cHTTP
{
private:
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

public:
    cHTTP();
    ~cHTTP();
    std::string getResponse(const std::string &_content) const;

private:
    sResponse initResponse(const std::string &_content) const;
};
