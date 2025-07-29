//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <iostream>
#include "Event.h"
#include <chrono>

class EventManager {
private:
    std::vector<Event> evenimente;

public:
    EventManager() = default;
    EventManager(const std::vector<Event> & events): evenimente(events) {}

    void addEvent(const Event& event);
    bool deleteEvent(unsigned int ID);
    bool editEvent(unsigned int ID, const Event & newEvent);
    void showEvents() const;
    Event* findEventByID(unsigned int ID);
    std::vector<Event> findEventsByTitle(const std::string & title) const;
    void notifyUpcomingEvents() const;
    void saveToFile(const std::string & filename) const;
    void loadFromFile(const std::string & filename);
    ~EventManager() = default;
};



#endif //EVENTMANAGER_H
