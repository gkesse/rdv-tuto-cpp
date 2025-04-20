#include "cServer.h"
#include "cServerInit.h"
#include <winsock2.h>
#include <iostream>

static const int DEF_WINSOCK_MAJOR_VERSION = 2;
static const int DEF_WINSOCK_MINOR_VERSION = 2;
static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;

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
        std::cout << "L'initialisation du point de terminaison a echoue."
                  << "|errorCode=" << oWSAStartup
                  << "|errorMsg=" << getLastError(oWSAStartup)
                  << "|WINSOCK_MAJOR_VERSION=" << DEF_WINSOCK_MAJOR_VERSION
                  << "|WINSOCK_MINOR_VERSION=" << DEF_WINSOCK_MINOR_VERSION
                  << std::endl;
        return;
    }

    cServerInit oServerRun;
    oServerRun.run();
}

std::string cServer::getLastError(int _error) const
{
    char oErrorMsg[DEF_WINSOCK_ERROR_MSG_LENGTH] = {0};
    int oLength = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                NULL,
                                _error,
                                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                oErrorMsg,
                                sizeof(oErrorMsg),
                                NULL);
    if (oLength > 0)
    {
        oErrorMsg[oLength - 1] = 0;
    }
    std::string oMessage = oErrorMsg;
    return oMessage;
}
