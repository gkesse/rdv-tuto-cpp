#include "cServerInit.h"
#include "cServerSocket.h"
#include "cErrorMsg.h"
#include <winsock2.h>
#include <iostream>

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
        std::cout << "[Error]:La creation du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return;
    }

    cServerSocket oServerSocket(oSocket);
    oServerSocket.run();
}
