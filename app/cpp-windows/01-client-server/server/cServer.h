#pragma once

#include <string>

class cServer
{
public:
    explicit cServer();
    ~cServer();
    void run();

private:
    std::string getLastError(int _error) const;
};
