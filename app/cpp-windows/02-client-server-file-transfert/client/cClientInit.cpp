#include "cClientInit.h"
#include "cClientSocket.h"
#include "cErrorMsg.h"
#include <winsock2.h>
#include <iostream>

cClientInit::cClientInit()
{
}

cClientInit::~cClientInit()
{
    WSACleanup();
}

bool cClientInit::run(const std::string &_request, std::string &_response) const
{
    SOCKET oSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (oSocket == INVALID_SOCKET)
    {
        std::cout << "La creation du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return false;
    }

    cClientSocket oClientSocket(oSocket);
    return oClientSocket.run(_request, _response);
}
