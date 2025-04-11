#include "cClientSocket.h"
#include <ws2tcpip.h>
#include <iostream>

static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;
static const char *DEF_WINSOCK_SERVER_ADDRESS = "127.0.0.1";
static const int DEF_WINSOCK_SERVER_PORT = 5555;
static const int DEF_WINSOCK_BUFFER_SIZE = 1024;

cClientSocket::cClientSocket(SOCKET _socket)
    : m_socket(_socket)
{
}

cClientSocket::~cClientSocket()
{
    closesocket(m_socket);
}

bool cClientSocket::run(const std::string &_request, std::string &_response)
{
    SOCKADDR_IN oServerAddress;

    InetPton(AF_INET, DEF_WINSOCK_SERVER_ADDRESS, &oServerAddress.sin_addr.s_addr);
    oServerAddress.sin_family = AF_INET;
    oServerAddress.sin_port = htons(DEF_WINSOCK_SERVER_PORT);

    if (connect(m_socket, reinterpret_cast<SOCKADDR *>(&oServerAddress), sizeof(oServerAddress)) == SOCKET_ERROR)
    {
        std::cout << "La connexion au point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return false;
    }

    if (sendData(_request))
    {
        recvData(_response);
    }

    return true;
}

bool cClientSocket::recvData(std::string &_response)
{
    char oBuffer[DEF_WINSOCK_BUFFER_SIZE];
    int oBytes = recv(m_socket, oBuffer, DEF_WINSOCK_BUFFER_SIZE - 1, 0);
    if (oBytes == SOCKET_ERROR)
    {
        std::cout << "La reception des donnees du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return false;
    }
    oBuffer[oBytes] = '\0';
    _response = oBuffer;
    return true;
}

bool cClientSocket::sendData(const std::string &_request)
{
    int oBytes = send(m_socket, _request.c_str(), (int)_request.length(), 0);
    if (oBytes == SOCKET_ERROR)
    {
        std::cout << "La reception des donnees du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return false;
    }
    return true;
}

std::string cClientSocket::getLastError(int _error) const
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
