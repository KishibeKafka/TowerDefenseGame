#include "timer.h"
#include <chrono>

void Timer::start_timer()
{
    start = std::chrono::system_clock::now();
}

std::chrono::duration< double > Timer::getCurrrentTime()
{
    auto cur = std::chrono::system_clock::now() - start;
    return cur;
}