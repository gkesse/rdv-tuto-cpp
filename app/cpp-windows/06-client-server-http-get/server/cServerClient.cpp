#include "cServerClient.h"
#include "cServerApp.h"
#include "cString.h"
#include "cErrorMsg.h"
#include <iostream>

// winsock2
static const int DEF_WINSOCK_BUFFER_SIZE = 1024;
static const int DEF_WINSOCK_BUFFER_MAX = 1 * 1024 * 1024; // 1 Mo

// limit
static const int DEF_DATA_LIMIT_SIZE = 100;

cServerClient::cServerClient(SOCKET _socket)
    : m_socket(_socket)
{
}

cServerClient::~cServerClient()
{
    closesocket(m_socket);
}

void cServerClient::run()
{
    std::string oRequest;
    std::string oResponse;

    if (recvData(oRequest))
    {
        cServerApp oApp;
        oApp.run(oRequest, oResponse);
    }
    else
    {
        oResponse = "Un probleme a ete rencontre.";
    }

    sendData(oResponse);

    std::cout << "[Request]:" << cString(oRequest).escape(DEF_DATA_LIMIT_SIZE) << std::endl;
    std::cout << "[Response]:" << cString(oResponse).escape(DEF_DATA_LIMIT_SIZE) << std::endl;
}

bool cServerClient::recvData(std::string &_request)
{
    std::string oRequest;
    char oBuffer[DEF_WINSOCK_BUFFER_SIZE];
    while (true)
    {
        int oBytes = recv(m_socket, oBuffer, DEF_WINSOCK_BUFFER_SIZE - 1, 0);
        if (oBytes == SOCKET_ERROR)
        {
            std::cout << "[Error]:La reception des donnees du point de terminaison a echoue."
                      << "|errorCode=" << GetLastError()
                      << "|errorMsg=" << getLastErrorMsg(GetLastError())
                      << std::endl;
            return false;
        }

        oRequest.append(oBuffer, oBytes);

        if (oRequest.size() >= DEF_WINSOCK_BUFFER_MAX)
        {
            std::cout << "[Error]:Le nombre maximal de donnees sur le point de terminaison a ete atteint."
                      << "|DEF_WINSOCK_BUFFER_MAX=" << DEF_WINSOCK_BUFFER_MAX
                      << std::endl;
            return false;
        }

        u_long oBytesIO;
        int isOK = ioctlsocket(m_socket, FIONREAD, &oBytesIO);

        if (isOK == SOCKET_ERROR)
        {
            std::cout << "[Error]:La lecture du nombre de donnees restantes sur le point de terminaison a echoue."
                      << "|errorCode=" << GetLastError()
                      << "|errorMsg=" << getLastErrorMsg(GetLastError())
                      << std::endl;
            return false;
        }

        if (oBytesIO == 0)
        {
            break;
        }
    }
    _request = oRequest;
    return true;
}

bool cServerClient::sendData(const std::string &_response)
{
    int oBytes = send(m_socket, _response.c_str(), (int)_response.length(), 0);
    if (oBytes == SOCKET_ERROR)
    {
        std::cout << "[Error]:La reception des donnees du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return false;
    }
    return true;
}
