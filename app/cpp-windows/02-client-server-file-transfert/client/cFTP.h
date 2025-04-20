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
    void sendFile(const std::string &_filename);

private:
    bool loadFile(const std::string &_filename, sFTP &_sFTP);
    std::string serialize(const sFTP &_sFTP);
};
