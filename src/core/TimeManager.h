#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

class TimeManager {
public: 
    TimeManager(const TimeManager&) = delete; 
    TimeManager& operator=(const TimeManager&) = delete;

    static TimeManager& GetInstance() {
        static TimeManager instance; 
        return instance; 
    }

private:
    explicit TimeManager() {}
};

#endif