#pragma once

#include <string>

class cServerApp
{
public:
    explicit cServerApp();
    ~cServerApp();
    void run(const std::string &_request, std::string &_response) const;
};
