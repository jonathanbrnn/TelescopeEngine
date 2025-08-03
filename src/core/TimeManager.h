#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <chrono>
#include <iostream>

class TimeManager {
public: 
    TimeManager(const TimeManager&) = delete; 
    TimeManager& operator=(const TimeManager&) = delete;

    static TimeManager& GetInstance() {
        static TimeManager instance; 
        return instance; 
    }

    void UpdateTime();

    float GetDeltaTime(); 

private:
    explicit TimeManager() : delta_time(0) {}

    std::chrono::high_resolution_clock::time_point original_time = std::chrono::high_resolution_clock::now();
    float delta_time;
};

#endif