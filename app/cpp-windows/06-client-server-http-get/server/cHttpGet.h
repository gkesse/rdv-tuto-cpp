#pragma once

#include "cHTTP.h"
#include <string>

class cHttpGet
{
public:
    using sRequest = cHTTP::sRequest;
    using STATUS_CODE = cHTTP::STATUS_CODE;

public:
    explicit cHttpGet();
    ~cHttpGet();
    void run(const sRequest &_requestHTTP, std::string &_responseText, std::string &_contentType, STATUS_CODE &_statusCode) const;
};
