#include "cClient.h"
#include "cClientInit.h"
#include "cErrorMsg.h"
#include <winsock2.h>
#include <iostream>

static const int DEF_WINSOCK_MAJOR_VERSION = 2;
static const int DEF_WINSOCK_MINOR_VERSION = 2;

cClient::cClient()
{
}

cClient::~cClient()
{
}

bool cClient::run(const std::string &_request, std::string &_response) const
{
    WSADATA oWSADATA;
    int oWSAStartup = WSAStartup(MAKEWORD(DEF_WINSOCK_MAJOR_VERSION, DEF_WINSOCK_MINOR_VERSION),
                                 &oWSADATA);

    if (oWSAStartup != 0)
    {

        std::cout << "L'initialisation du point de terminaison a echoue."
                  << "|errorCode=" << oWSAStartup
                  << "|errorMsg=" << getLastErrorMsg(oWSAStartup)
                  << "|WINSOCK_MAJOR_VERSION=" << DEF_WINSOCK_MAJOR_VERSION
                  << "|WINSOCK_MINOR_VERSION=" << DEF_WINSOCK_MINOR_VERSION
                  << std::endl;
        return false;
    }

    cClientInit oClientRun;
    return oClientRun.run(_request, _response);
}
