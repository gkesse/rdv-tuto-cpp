#pragma once

#include <string>

class cServerInit
{
    friend class cServer;

private:
    explicit cServerInit();
    ~cServerInit();
    void run();
};
