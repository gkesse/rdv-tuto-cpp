#include "cClassA.h"
#include "cClassB.h"
#include "cClassC.h"

int main(int _argc, char **_argv)
{
    {
        cClassA<cClassB> oClassB;
        oClassB.print();
    }
    {
        cClassC<cClassB> oClassB;
        oClassB.print();
    }
    return 0;
}
