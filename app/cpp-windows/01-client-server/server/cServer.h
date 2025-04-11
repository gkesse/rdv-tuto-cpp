#pragma once

#include <string>

class cServer
{
public:
    explicit cServer(int _argc, char **_argv);
    ~cServer();
    void run();

private:
    std::string getLastError(int _error) const;

private:
    int m_argc;
    char **m_argv;
};
