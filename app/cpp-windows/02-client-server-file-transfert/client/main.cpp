#include "cFTP.h"

static const std::string DEF_INPUT_CV_FILE = "../../data/input/cv.txt";
static const std::string DEF_INPUT_IMAGE_FILE = "../../data/input/cpp.png";

int main(int _argc, char **_argv)
{
    cFTP oFTP;
    oFTP.sendFile(DEF_INPUT_CV_FILE);
    oFTP.sendFile(DEF_INPUT_IMAGE_FILE);
    return 0;
}
