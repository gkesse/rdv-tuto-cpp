#pragma once

#include <string>

class cFTP
{
public:
    struct sFTP
    {
        std::string path;
        std::string filename;
        size_t size;
        std::string data;
    };

public:
    explicit cFTP();
    ~cFTP();
    bool saveFile(const std::string &_request, sFTP &_sFTP);

private:
    bool deserialize(const std::string &_request, sFTP &_sFTP);
};
