#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <semaphore>

static const int DEF_SEMAPHORE_THREAD_MAX = 4;
static const int DEF_APP_THREAD_TOTAL = 10;

static std::counting_semaphore<DEF_SEMAPHORE_THREAD_MAX> gSemaphore(DEF_SEMAPHORE_THREAD_MAX);

using namespace std::chrono_literals;

static void onThread(const std::string &_name);

int main(int _argc, char **_argv)
{
    std::vector<std::thread> oThreads;
    for (int i = 0; i < DEF_APP_THREAD_TOTAL; i++)
    {
        oThreads.emplace_back(onThread, "[Thread" + std::string(1, 'A' + i) + "]");
    }
    for (auto &oThread : oThreads)
    {
        oThread.join();
    }
    return 0;
}

static void onThread(const std::string &_name)
{
    std::stringstream oWaitMsg;
    oWaitMsg << _name << " : " << "En attente de traitement." << std::endl;
    std::cout << oWaitMsg.str();

    gSemaphore.acquire();
    std::stringstream oStartMsg;
    std::stringstream oEndMsg;
    oStartMsg << _name << " : " << "Demarrage du traitement." << std::endl;
    oEndMsg << _name << " : " << "Fin du traitement." << std::endl;

    std::cout << oStartMsg.str();
    std::this_thread::sleep_for(1s);
    std::cout << oEndMsg.str();
    gSemaphore.release();
}
