#include "cServerClient.h"
#include "cFTP.h"
#include "cString.h"
#include "cErrorMsg.h"
#include <iostream>

// winsock2
static const int DEF_WINSOCK_BUFFER_SIZE = 1024;
static const int DEF_WINSOCK_BUFFER_MAX = 1 * 1024 * 1024; // 1 Mo

// limit
static const int DEF_REQUEST_LIMIT_SIZE = 100;

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
    cFTP::sFTP aFTP;

    if (recvData(oRequest))
    {
        cFTP oFTP;
        if (oFTP.saveFile(oRequest, aFTP))
        {
            oResponse = "Votre requete a ete traite avec succes.";
        }
        else
        {
            oResponse = "Le chargement du fichier a echoue.";
        }
    }
    else
    {
        oResponse = "Un probleme a ete rencontre.";
    }

    sendData(oResponse);

    std::cout << "[Client] : ================================" << std::endl;
    std::cout << "[Client] : sFTP.path=" << aFTP.path << std::endl;
    std::cout << "[Client] : sFTP.filename=" << aFTP.filename << std::endl;
    std::cout << "[Client] : sFTP.size=" << aFTP.size << std::endl;
    std::cout << "[Client] : sFTP.data.size()=" << aFTP.data.size() << std::endl;
    std::cout << "[Client] : sFTP.data=" << cString(aFTP.data).limit(DEF_REQUEST_LIMIT_SIZE).oneLine() << std::endl;
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
                      << "|errorMsg=" << getLastErrorMsg(GetLastError())
                      << std::endl;
            return false;
        }

        oRequest.append(oBuffer, oBytes);

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
        std::cout << "La reception des donnees du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return false;
    }
    return true;
}
