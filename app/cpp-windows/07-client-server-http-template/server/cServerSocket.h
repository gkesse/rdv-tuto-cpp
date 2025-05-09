#pragma once

#include <string>
#include <winsock2.h>

class cServerSocket
{
    friend class cServerInit;

private:
    explicit cServerSocket(SOCKET _socket);
    ~cServerSocket();
    void run();

private:
    static void onAccept(SOCKET _client);

private:
    SOCKET m_socket;
};
