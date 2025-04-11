#pragma once

#include <string>
#include <winsock2.h>

class cClientSocket
{
    friend class cClientInit;

private:
    explicit cClientSocket(SOCKET _socket);
    ~cClientSocket();
    bool run(const std::string &_request, std::string &_response);

private:
    bool recvData(std::string &_response);
    bool sendData(const std::string &_request);
    std::string getLastError(int _error) const;

private:
    SOCKET m_socket;
};
