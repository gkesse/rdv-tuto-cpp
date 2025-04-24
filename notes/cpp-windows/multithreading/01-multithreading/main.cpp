#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

static void onThread(const std::string &_name);

int main(int _argc, char **_argv)
{
    std::thread oThreadA(onThread, "[ThreadA]");
    std::thread oThreadB(onThread, "[ThreadB]");
    oThreadA.join();
    oThreadB.join();
    return 0;
}

static void onThread(const std::string &_name)
{
    std::cout << _name << " : " << "Demarrage du traitement." << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << _name << " : " << "Fin du traitement." << std::endl;
}
