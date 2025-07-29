//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#include "EventManager.h"


void EventManager::addEvent(const Event &event) {
    evenimente.push_back(event);
    std::cout<<"Evenimentul "<<event.getTitle()<<" a fost adaugat cu succes in planificator."<<std::endl;
}

bool EventManager::deleteEvent(unsigned int ID) {
   auto initialSize = evenimente.size();
    evenimente.erase(
        std::remove_if(evenimente.begin(), evenimente.end(), [ID](const Event& ev){return ev.getID() == ID;}), evenimente.end());

    return evenimente.size() < initialSize;
}

bool EventManager::editEvent(unsigned int ID, const Event &newEvent) {
    for (auto ev: evenimente)
        if (ev.getID() == ID) {
            auto tempID = ev.getID();
            ev = newEvent;
            ev.setID(tempID);
            return true;
        }
    return false;
}

void EventManager::showEvents() const {
    for (const auto &ev: evenimente) {
        ev.print();
        std::cout<<"-----"<<std::endl;
    }
}

Event * EventManager::findEventByID(unsigned int ID) {
    for ( auto &ev:evenimente)
        if (ev.getID() == ID)
            return &ev;
    return nullptr;
}

std::vector<Event> EventManager::findEventsByTitle(const std::string &title) const {
    std::vector<Event> eventsByTitle;
    for (const auto & ev: evenimente)
        if (ev.getTitle() == title)
            eventsByTitle.push_back(ev);
    return eventsByTitle;
}

void EventManager::notifyUpcomingEvents() const {
    using namespace::std::chrono;

    auto now = system_clock::now();

    auto ld = floor<days>(now);

    year_month_day data_ymd{ld};
    int year = int(data_ymd.year());
    int month = unsigned(data_ymd.month());
    int day = unsigned(data_ymd.day());

    hh_mm_ss timp_hms{now-ld};
    int hour = timp_hms.hours().count();
    int minute = timp_hms.minutes().count();

    std::string dataNow = std::to_string(day) +'/' + std::to_string(month) + '/' + std::to_string(year);

    std::string timpNow = std::to_string(hour) +':' + std::to_string(minute);

}

void EventManager::saveToFile(const std::string &filename) const {
}

void EventManager::loadFromFile(const std::string &filename) {
}
