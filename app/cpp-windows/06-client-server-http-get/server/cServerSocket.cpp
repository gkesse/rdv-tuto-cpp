#include "cServerSocket.h"
#include "cServerClient.h"
#include "cErrorMsg.h"
#include <future>
#include <iostream>

// winsock2
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
        std::cout << "[Error]:La liaison de l'adresse du point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return;
    }

    if ((listen(m_socket, DEF_WINSOCK_SERVER_BACKLOG)) == SOCKET_ERROR)
    {
        std::cout << "[Error]:L'initialisation du nombre de connexions au point de terminaison a echoue."
                  << "|errorCode=" << GetLastError()
                  << "|errorMsg=" << getLastErrorMsg(GetLastError())
                  << std::endl;
        return;
    }

    std::cout << "[Info]:Le serveur a demarre..."
              << "|port=" << DEF_WINSOCK_SERVER_PORT
              << std::endl;

    while (true)
    {
        SOCKADDR_IN oAddress;
        int oSize = sizeof(oAddress);
        SOCKET oClient = accept(m_socket, reinterpret_cast<SOCKADDR *>(&oAddress), &oSize);

        if (oClient == INVALID_SOCKET)
        {
            std::cout << "[Error]:La connexion d'un client au point de terminaison a echoue."
                      << "|errorCode=" << GetLastError()
                      << "|errorMsg=" << getLastErrorMsg(GetLastError())
                      << std::endl;
            continue;
        }

        auto oFuture = std::async(std::launch::async, onAccept, oClient);
    }
}

void cServerSocket::onAccept(SOCKET _client)
{
    cServerClient oServerClient(_client);
    oServerClient.run();
}
