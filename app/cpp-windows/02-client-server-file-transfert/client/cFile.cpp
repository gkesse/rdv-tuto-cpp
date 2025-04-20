#include "cFile.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

cFile::cFile(const std::string &_filename)
    : m_filename(_filename)
{
}

cFile::~cFile()
{
}

bool cFile::exitsFile() const
{
    std::ifstream oFile(m_filename);
    return oFile.good();
}

bool cFile::isFile() const
{
    std::filesystem::path oPath(m_filename);
    return std::filesystem::is_regular_file(oPath);
}

bool cFile::isDir() const
{
    std::filesystem::path oPath(m_filename);
    return std::filesystem::is_directory(oPath);
}

std::string cFile::getFilename() const
{
    std::filesystem::path oPath(m_filename);
    return oPath.filename().string();
}

std::string cFile::getBasename() const
{
    std::filesystem::path oPath(m_filename);
    return oPath.stem().string();
}

std::string cFile::getExtension() const
{
    std::filesystem::path oPath(m_filename);
    return oPath.extension().string();
}

std::string cFile::getPath() const
{
    std::filesystem::path oPath(m_filename);
    return oPath.parent_path().string();
}

std::string cFile::getAbsolutePath() const
{
    try
    {
        std::filesystem::path oPath(m_filename);
        return std::filesystem::canonical(oPath).string();
    }
    catch (...)
    {
    }
    return "";
}

bool cFile::createDirectory() const
{
    try
    {
        std::filesystem::create_directories(m_filename);
        return true;
    }
    catch (...)
    {
    }
    return false;
}

std::string cFile::readText() const
{
    std::ifstream oFile(m_filename);
    std::stringstream oBuffer;
    oBuffer << oFile.rdbuf();
    return oBuffer.str();
}

void cFile::writeText(const std::string &_data) const
{
    std::ofstream oFile(m_filename);
    oFile << _data.c_str();
}

std::string cFile::readBin() const
{
    std::ifstream oFile(m_filename, std::ios::in | std::ios::binary);
    std::vector<char> oData = std::vector<char>(std::istreambuf_iterator<char>(oFile), std::istreambuf_iterator<char>());
    return std::string(&oData[0], oData.size());
}

void cFile::writeBin(const std::string &_data) const
{
    std::ofstream oFile(m_filename, std::ios::out | std::ios::binary);
    oFile.write(&_data[0], _data.size());
}
