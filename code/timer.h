#pragma once
#include <chrono>
#include <thread>

class Timer
{
    std::chrono::system_clock::time_point start;
public:
    void start_timer();                                 // 启动计时器
    std::chrono::duration< double > getCurrrentTime();  // 1 second
};