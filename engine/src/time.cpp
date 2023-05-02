#include "time.hpp"

Time::Time()
{
    lastTime = std::chrono::high_resolution_clock::now();
}

float Time::deltaTime()
{
    currentTime = std::chrono::high_resolution_clock::now();
    auto timeDiff = currentTime - lastTime;
    float deltaTime = std::chrono::duration<float, std::milli>(timeDiff).count() / 1000.0f;
    lastTime = currentTime;
    return deltaTime;
}