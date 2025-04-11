#include "cServer.h"

int main(int _argc, char **_argv)
{
    cServer oServer(_argc, _argv);
    oServer.run();
    return 0;
}
