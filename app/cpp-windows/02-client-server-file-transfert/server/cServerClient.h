#pragma once

#include <string>
#include <winsock2.h>

class cServerClient
{
    friend class cServerSocket;

private:
    explicit cServerClient(SOCKET _socket);
    ~cServerClient();
    void run();

private:
    bool recvData(std::string &_request);
    bool sendData(const std::string &_response);
    std::string getLastError(int _error) const;

private:
    SOCKET m_socket;
};
