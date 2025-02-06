#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class EventManager {
    public: 
    explicit EventManager(); 

    private: 
    EventManager(const EventManager&) = delete; 
    EventManager& operator=(const EventManager&) = delete; 
}; 

#endif