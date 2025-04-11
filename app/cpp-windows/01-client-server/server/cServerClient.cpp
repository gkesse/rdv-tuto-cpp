#include "cServerClient.h"
#include <iostream>

static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;
static const int DEF_WINSOCK_BUFFER_SIZE = 1024;

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
    std::string oResponse = "Un probleme a ete rencontre.";
    if (recvData(oRequest))
    {
        oResponse = "Votre requete a ete traite avec succes.";
    }
    sendData(oResponse);

    std::cout << "[Client] : " << oRequest << std::endl;
    std::cout << "[Server] : " << oResponse << std::endl;
}

bool cServerClient::recvData(std::string &_request)
{
    char oBuffer[DEF_WINSOCK_BUFFER_SIZE];
    int oBytes = recv(m_socket, oBuffer, DEF_WINSOCK_BUFFER_SIZE, 0);
    if (oBytes == SOCKET_ERROR)
    {
        std::cout << "La reception des donnees du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return false;
    }
    oBuffer[oBytes] = '\0';
    _request = oBuffer;
    return true;
}

bool cServerClient::sendData(const std::string &_response)
{
    int oBytes = send(m_socket, _response.c_str(), (int)_response.length(), 0);
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

std::string cServerClient::getLastError(int _error) const
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
