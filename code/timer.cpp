#include "timer.h"
#include <chrono>
#include <mutex>
std::mutex m;

void Timer::start_timer()
{
    start = std::chrono::system_clock::now();
}

std::chrono::duration< double > Timer::getCurrrentTime()
{
    auto cur = std::chrono::system_clock::now() - start;
    return cur;
}

void Timer::fixedExecute(void (*func)(void))
{
    while (true)
    {
        std::lock_guard< std::mutex > mutex(m);
        auto before = std::chrono::system_clock::now();

        func();

        auto after = std::chrono::system_clock::now();
        auto cost = after - before;
        auto wait = dt - cost;
        if (wait <=
            std::chrono::duration< long long, std::ratio< 1, 1000 > >::zero())
            continue;
        if (wait > std::chrono::milliseconds(1))
            std::this_thread::sleep_for(wait - std::chrono::milliseconds(1));
        auto next = before + dt;
        while (std::chrono::system_clock::now() < next) {}
    }
}