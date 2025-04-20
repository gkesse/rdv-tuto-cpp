#pragma once

#include <string>

class cFile
{
public:
    explicit cFile(const std::string &_filename);
    ~cFile();
    bool exitsFile() const;
    bool isFile() const;
    bool isDir() const;

    std::string getFilename() const;
    std::string getBasename() const;
    std::string getExtension() const;
    std::string getPath() const;
    std::string getAbsolutePath() const;

    bool createDirectory() const;

    std::string readText() const;
    void writeText(const std::string &_data) const;
    std::string readBin() const;
    void writeBin(const std::string &_data) const;

private:
    std::string m_filename;
};
