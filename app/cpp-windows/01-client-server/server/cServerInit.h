#pragma once

#include <string>

class cServerInit
{
    friend class cServer;

private:
    explicit cServerInit();
    ~cServerInit();
    void run();

private:
    std::string getLastError(int _error) const;
};
