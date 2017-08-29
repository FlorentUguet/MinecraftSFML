#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    void reset();
    void restart();
    int getElapsedMS();
    double getElapsed(double factor = 1.0);

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    double elapsed = 0.0;
    bool stopped = true;
};

#endif // TIMER_H
