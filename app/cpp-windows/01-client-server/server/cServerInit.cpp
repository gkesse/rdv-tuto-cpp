#include "cServerInit.h"
#include "cServerSocket.h"
#include <winsock2.h>
#include <iostream>

static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;

cServerInit::cServerInit()
{
}

cServerInit::~cServerInit()
{
    WSACleanup();
}

void cServerInit::run()
{
    SOCKET oSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (oSocket == INVALID_SOCKET)
    {
        std::cout << "La creation du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return;
    }

    cServerSocket oServerSocket(oSocket);
    oServerSocket.run();
}

std::string cServerInit::getLastError(int _error) const
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
