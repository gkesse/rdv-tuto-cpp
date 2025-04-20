#pragma once

#include <string>

class cClient
{
public:
    explicit cClient();
    ~cClient();
    bool run(const std::string &_request, std::string &_response) const;
};
