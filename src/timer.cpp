#include "timer.h"

Timer::Timer()
{

}

void Timer::start()
{
    this->startTime = std::chrono::high_resolution_clock::now();
    this->stopped = false;
}

void Timer::stop()
{
    this->elapsed = this->getElapsed();
    this->stopped = true;
}

void Timer::reset()
{
    this->elapsed = 0.0;
}

void Timer::restart()
{
    this->reset();
    this->start();
}

int Timer::getElapsedMS()
{
    return (int)getElapsed(1000);
}

double Timer::getElapsed(double factor)
{
    double d = 0.0f;

    if(!stopped)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - this->startTime;
        d = this->elapsed + diff.count();
    }
    else
    {
        d = this->elapsed;
    }

    return d * factor;
}
