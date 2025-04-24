#include <iostream>

static constexpr int BUFFER_SIZE()
{
    return 5;
}

int main(int _argc, char **_argv)
{
    int oBuffer[BUFFER_SIZE()];

    for (int i = 0; i < BUFFER_SIZE(); i++)
    {
        oBuffer[i] = i * BUFFER_SIZE();
    }

    for (int i = 0; i < BUFFER_SIZE(); i++)
    {
        std::cout << "[Info]:oBuffer[" << i << "]=" << oBuffer[i]
                  << std::endl;
    }
    return 0;
}
