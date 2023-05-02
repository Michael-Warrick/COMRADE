#include <chrono>

class Time {
public:
    Time();
    float deltaTime();
    float now();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
};
