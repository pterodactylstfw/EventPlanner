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
    unsigned int currentID = 0;

public:
    EventManager() = default;
    EventManager(const std::vector<Event> & events): evenimente(events) {}

    int size() const;

    unsigned int getNextID() { return currentID++; }
    void resetCurrentID(unsigned int id) { currentID = id; }
    const std::vector<Event> &getEvents() const { return evenimente; }

    void addEvent(const Event& event);
    bool deleteEvent(unsigned int ID);
    bool editEvent(unsigned int ID, const Event & newEvent);
    std::vector<std::string> showEvents() const;
    Event* findEventByID(unsigned int ID);
    std::vector<Event> findEventsByTitle(const std::string & title) const;
    std::vector<std::string> notifyUpcomingEvents() const;
    void saveToFile(const std::string & filename) const;
    void loadFromFile(const std::string & filename);
    ~EventManager() = default;
};



#endif //EVENTMANAGER_H
