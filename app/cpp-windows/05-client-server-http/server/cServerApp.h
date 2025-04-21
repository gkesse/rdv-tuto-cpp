#pragma once

#include <string>

class cServerApp
{
    friend class cServerClient;

private:
    explicit cServerApp();
    ~cServerApp();
    void run(const std::string &_request, std::string &_response);
};
