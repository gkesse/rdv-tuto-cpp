#include "cClientSocket.h"
#include "cErrorMsg.h"
#include <ws2tcpip.h>
#include <iostream>

// winsock2
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
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
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
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return false;
    }
    oBuffer[oBytes] = '\0';
    _response = oBuffer;
    return true;
}

bool cClientSocket::sendData(const std::string &_request)
{
    int oBytes = send(m_socket, &_request[0], (int)_request.length(), 0);
    if (oBytes == SOCKET_ERROR)
    {
        std::cout << "La reception des donnees du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return false;
    }
    return true;
}
