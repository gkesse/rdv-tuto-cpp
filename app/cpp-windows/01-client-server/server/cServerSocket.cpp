#include "cServerSocket.h"
#include "cServerClient.h"
#include <future>
#include <iostream>

static const int DEF_WINSOCK_ERROR_MSG_LENGTH = 512;
static const int DEF_WINSOCK_SERVER_PORT = 5555;
static const int DEF_WINSOCK_SERVER_BACKLOG = 10;

cServerSocket::cServerSocket(SOCKET _socket)
    : m_socket(_socket)
{
}

cServerSocket::~cServerSocket()
{
    closesocket(m_socket);
}

void cServerSocket::run()
{
    SOCKADDR_IN oServerAddr;
    oServerAddr.sin_addr.s_addr = INADDR_ANY;
    oServerAddr.sin_family = AF_INET;
    oServerAddr.sin_port = htons(DEF_WINSOCK_SERVER_PORT);

    if ((bind(m_socket, reinterpret_cast<SOCKADDR *>(&oServerAddr),
              sizeof(oServerAddr))) == SOCKET_ERROR)
    {
        std::cout << "La liaison de l'adresse du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return;
    }

    if ((listen(m_socket, DEF_WINSOCK_SERVER_BACKLOG)) == SOCKET_ERROR)
    {
        std::cout << "L'initialisation du nombre de connexions au point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastError(GetLastError())
                  << std::endl;
        return;
    }

    std::cout << "Le serveur a demarre..."
              << "|port=" << DEF_WINSOCK_SERVER_PORT
              << std::endl;

    while (true)
    {
        SOCKADDR_IN oAddress;
        int oSize = sizeof(oAddress);
        SOCKET oClient = accept(m_socket, reinterpret_cast<SOCKADDR *>(&oAddress), &oSize);

        if (oClient == INVALID_SOCKET)
        {
            std::cout << "La connexion d'un client au point de terminaison a echoue."
                      << "|errorCode=" << GetLastError()
                      << "|errorMsg=" << getLastError(GetLastError())
                      << std::endl;
            continue;
        }

        auto fut = std::async(std::launch::async, onAccept, oClient);
    }
}

void cServerSocket::onAccept(SOCKET _client)
{
    cServerClient oServerClient(_client);
    oServerClient.run();
}

std::string cServerSocket::getLastError(int _error) const
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
