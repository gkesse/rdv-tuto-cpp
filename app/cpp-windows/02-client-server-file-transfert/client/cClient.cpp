#include "cClient.h"
#include "cClientInit.h"
#include <winsock2.h>
#include <iostream>

static const int DEF_WINSOCK_MAJOR_VERSION = 2;
static const int DEF_WINSOCK_MINOR_VERSION = 2;
static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;

cClient::cClient(int _argc, char **_argv)
    : m_argc(_argc),
      m_argv(_argv)
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
                  << "|errorMsg=" << getLastError(oWSAStartup)
                  << "|WINSOCK_MAJOR_VERSION=" << DEF_WINSOCK_MAJOR_VERSION
                  << "|WINSOCK_MINOR_VERSION=" << DEF_WINSOCK_MINOR_VERSION
                  << std::endl;
        return false;
    }

    cClientInit oClientRun;
    return oClientRun.run(_request, _response);
}

std::string cClient::getLastError(int _error) const
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
