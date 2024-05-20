#pragma once
#include <chrono>
#include <mutex>
#include <thread>
const std::chrono::milliseconds dt(16);

class Timer
{
    std::chrono::system_clock::time_point start;
public:
    void start_timer();                                 // 启动计时器
    std::chrono::duration< double > getCurrrentTime();  // 1 second
    void fixedExecute(void (*func)(void));
};