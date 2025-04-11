#pragma once

#include <string>

class cFile
{
public:
    explicit cFile(const std::string &_filename);
    ~cFile();
    bool exitsFile() const;
    std::string readText() const;
    std::string readBin() const;

private:
    std::string m_filename;
};
