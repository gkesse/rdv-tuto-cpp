#pragma once

#include <string>

class cClientInit
{
    friend class cClient;

private:
    explicit cClientInit();
    ~cClientInit();
    bool run(const std::string &_request, std::string &_response) const;
};
