#pragma once

#include <string>

class cClient
{
public:
    explicit cClient(int _argc, char **_argv);
    ~cClient();
    bool run(const std::string &_request, std::string &_response) const;

private:
    std::string getLastError(int _error) const;

private:
    int m_argc;
    char **m_argv;
};
