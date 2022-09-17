#include <chrono>
#include <iostream>
#include <string>

class Timer
{
public:

    Timer();

    /// <returns>Returns time elapsed in milliseconds as a double</returns>
    const double Time();


    /// <returns>Returns time elapsed in milliseconds as a formatted string</returns>
    const std::string Time_str();

    ~Timer();

private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    bool used = false;
};