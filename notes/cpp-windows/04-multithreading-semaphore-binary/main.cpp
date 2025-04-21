#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>

static const int DEF_SEMAPHORE_INIT_LOCKED = 0;
static const int DEF_SEMAPHORE_INIT_UNLOCKED = 1;

static std::binary_semaphore gSemaphore(DEF_SEMAPHORE_INIT_UNLOCKED);

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
    gSemaphore.acquire();
    std::cout << _name << " : " << "Demarrage du traitement." << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << _name << " : " << "Fin du traitement." << std::endl;
    gSemaphore.release();
}
