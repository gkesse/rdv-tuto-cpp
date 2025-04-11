#include "cFile.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

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

std::string cFile::readText() const
{
    std::ifstream oFile(m_filename);
    std::stringstream oBuffer;
    oBuffer << oFile.rdbuf();
    return oBuffer.str();
}

void cFile::writeText(const std::string &_data)
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
