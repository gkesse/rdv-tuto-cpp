#include "cServerClient.h"
#include "cFile.h"
#include <iostream>

static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;
static const int DEF_WINSOCK_BUFFER_SIZE = 1024;
static const int DEF_WINSOCK_BUFFER_MAX = 1 * 1024 * 1024; // 1 Mo
static const std::string DEF_OUTPUT_FILENAME = "../../data/output/output.txt";

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
        cFile oFile(DEF_OUTPUT_FILENAME);
        oFile.writeText(oRequest);
        oResponse = "Votre requete a ete traite avec succes.";
    }

    sendData(oResponse);

    std::cout << "[Client] : DEF_OUTPUT_FILENAME=" << DEF_OUTPUT_FILENAME << std::endl;
    std::cout << "[Server] : " << oResponse << std::endl;
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
            std::cout << "La reception des donnees du point de terminaison a echoue."
                      << "|errorCode=" << GetLastError()
                      << "|errorMsg=" << getLastError(GetLastError())
                      << std::endl;
            return false;
        }
        oBuffer[oBytes] = '\0';
        oRequest += oBuffer;

        if (oRequest.size() >= DEF_WINSOCK_BUFFER_MAX)
        {
            std::cout << "Le nombre maximal de donnees sur le point de terminaison a ete atteint."
                      << "|DEF_WINSOCK_BUFFER_MAX=" << DEF_WINSOCK_BUFFER_MAX
                      << std::endl;
            return false;
        }

        u_long oBytesIO;
        int isOK = ioctlsocket(m_socket, FIONREAD, &oBytesIO);

        if (isOK == SOCKET_ERROR)
        {
            std::cout << "La lecture du nombre de donnees restantes sur le point de terminaison a echoue."
                      << "|errorCode=" << GetLastError()
                      << "|errorMsg=" << getLastError(GetLastError())
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
