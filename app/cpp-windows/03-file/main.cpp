#include "cFile.h"
#include <iostream>

static const std::string DEF_INPUT_PATH = "../../data/input";
static const std::string DEF_OUTPUT_PATH = "../../data/output";
static const std::string DEF_INPUT_IMAGE_FILE = "../../data/input/cpp.png";
static const std::string DEF_INPUT_CV_FILE = "../../data/input/cv.txt";
static const std::string DEF_INPUT_NO_IMAGE_FILE = "../../data/input/no-file.img";
static const std::string DEF_INPUT_NO_PATH = "../../data/input/no-path";
static const std::string DEF_OUTPUT_NEW_PATH = "../../data/output/new/path";
static const std::string DEF_OUTPUT_IMAGE_FILE = "../../data/output/image/cpp.png";
static const std::string DEF_OUTPUT_CV_FILE = "../../data/output/text/cv.txt";

int main(int, char **)
{
    {
        cFile oFile(DEF_INPUT_IMAGE_FILE);
        std::cout << DEF_INPUT_IMAGE_FILE << std::endl
                  << "|oFile.exitsFile()=" << oFile.exitsFile() << std::endl
                  << "|oFile.isFile()=" << oFile.isFile() << std::endl
                  << "|oFile.isDir()=" << oFile.isDir() << std::endl
                  << "|oFile.getFilename()=" << oFile.getFilename() << std::endl
                  << "|oFile.getBasename()=" << oFile.getBasename() << std::endl
                  << "|oFile.getExtension()=" << oFile.getExtension() << std::endl
                  << "|oFile.getPath()=" << oFile.getPath() << std::endl
                  << "|oFile.getAbsolutePath()=" << oFile.getAbsolutePath() << std::endl
                  << std::endl;
    }
    {
        cFile oFile(DEF_INPUT_NO_IMAGE_FILE);
        std::cout << DEF_INPUT_NO_IMAGE_FILE << std::endl
                  << "|oFile.exitsFile()=" << oFile.exitsFile() << std::endl
                  << "|oFile.isFile()=" << oFile.isFile() << std::endl
                  << "|oFile.isDir()=" << oFile.isDir() << std::endl
                  << "|oFile.getFilename()=" << oFile.getFilename() << std::endl
                  << "|oFile.getBasename()=" << oFile.getBasename() << std::endl
                  << "|oFile.getExtension()=" << oFile.getExtension() << std::endl
                  << "|oFile.getPath()=" << oFile.getPath() << std::endl
                  << "|oFile.getAbsolutePath()=" << oFile.getAbsolutePath() << std::endl
                  << std::endl;
    }
    {
        cFile oFile(DEF_INPUT_PATH);
        std::cout << DEF_INPUT_PATH << std::endl
                  << "|oFile.exitsFile()=" << oFile.exitsFile() << std::endl
                  << "|oFile.isFile()=" << oFile.isFile() << std::endl
                  << "|oFile.isDir()=" << oFile.isDir() << std::endl
                  << "|oFile.getFilename()=" << oFile.getFilename() << std::endl
                  << "|oFile.getBasename()=" << oFile.getBasename() << std::endl
                  << "|oFile.getExtension()=" << oFile.getExtension() << std::endl
                  << "|oFile.getPath()=" << oFile.getPath() << std::endl
                  << "|oFile.getAbsolutePath()=" << oFile.getAbsolutePath() << std::endl
                  << std::endl;
    }
    {
        cFile oFile(DEF_INPUT_NO_PATH);
        std::cout << DEF_INPUT_NO_PATH << std::endl
                  << "|oFile.exitsFile()=" << oFile.exitsFile() << std::endl
                  << "|oFile.isFile()=" << oFile.isFile() << std::endl
                  << "|oFile.isDir()=" << oFile.isDir() << std::endl
                  << "|oFile.getFilename()=" << oFile.getFilename() << std::endl
                  << "|oFile.getBasename()=" << oFile.getBasename() << std::endl
                  << "|oFile.getExtension()=" << oFile.getExtension() << std::endl
                  << "|oFile.getPath()=" << oFile.getPath() << std::endl
                  << "|oFile.getAbsolutePath()=" << oFile.getAbsolutePath() << std::endl
                  << std::endl;
    }
    {
        cFile oFile(DEF_OUTPUT_NEW_PATH);
        std::cout << DEF_OUTPUT_NEW_PATH << std::endl
                  << "|oFile.createDirectory()=" << oFile.createDirectory() << std::endl
                  << std::endl;
        oFile.createDirectory();
    }
    {
        cFile oInput(DEF_INPUT_CV_FILE);
        std::string oCV = oInput.readText();
        cFile oOutput(DEF_OUTPUT_CV_FILE);
        if (cFile(oOutput.getPath()).createDirectory())
        {
            oOutput.writeText(oCV);
        }

        std::cout << DEF_INPUT_CV_FILE << std::endl
                  << DEF_OUTPUT_CV_FILE << std::endl
                  << "|oInput.readText()=" << "readText" << std::endl
                  << "|oOutput.writeText()=" << "writeBin" << std::endl
                  << "|oCV.length()=" << oCV.length() << std::endl
                  << "|oCV.size()=" << oCV.size() << std::endl
                  << std::endl;
    }
    {
        cFile oInput(DEF_INPUT_IMAGE_FILE);
        std::string oImage = oInput.readBin();
        cFile oOutput(DEF_OUTPUT_IMAGE_FILE);
        if (cFile(oOutput.getPath()).createDirectory())
        {
            oOutput.writeBin(oImage);
        }

        std::cout << DEF_INPUT_IMAGE_FILE << std::endl
                  << DEF_OUTPUT_IMAGE_FILE << std::endl
                  << "|oInput.readBin()=" << "readBin" << std::endl
                  << "|oOutput.writeBin()=" << "writeBin" << std::endl
                  << "|oImage.length()=" << oImage.length() << std::endl
                  << "|oImage.size()=" << oImage.size() << std::endl
                  << std::endl;
    }
}
