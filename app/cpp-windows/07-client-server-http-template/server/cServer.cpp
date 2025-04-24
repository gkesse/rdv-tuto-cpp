#include "cServer.h"
#include "cServerInit.h"
#include "cErrorMsg.h"
#include <winsock2.h>
#include <iostream>

// winsock2
static const int DEF_WINSOCK_MAJOR_VERSION = 2;
static const int DEF_WINSOCK_MINOR_VERSION = 2;

cServer::cServer()
{
}

cServer::~cServer()
{
}

void cServer::run()
{
    WSADATA oWSADATA;
    int oWSAStartup = WSAStartup(MAKEWORD(DEF_WINSOCK_MAJOR_VERSION, DEF_WINSOCK_MINOR_VERSION),
                                 &oWSADATA);

    if (oWSAStartup != 0)
    {
        std::cout << "[Error]:L'initialisation du point de terminaison a echoue."
                  << "|errorCode=" << oWSAStartup
                  << "|errorMsg=" << getLastErrorMsg(oWSAStartup)
                  << "|WINSOCK_MAJOR_VERSION=" << DEF_WINSOCK_MAJOR_VERSION
                  << "|WINSOCK_MINOR_VERSION=" << DEF_WINSOCK_MINOR_VERSION
                  << std::endl;
        return;
    }

    cServerInit oServerRun;
    oServerRun.run();
}
