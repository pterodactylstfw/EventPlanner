//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#include "EventManager.h"
#include <fstream>

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
    for (auto &ev: evenimente)
        if (ev.getID() == ID) {
            auto tempID = ev.getID();
            ev = newEvent;
            ev.setID(tempID);
            return true;
        }
    return false;
}

void EventManager::showEvents() const {
    if (evenimente.size()==0)
        std::cout<<"Nu exista evenimente de afisat!"<<std::endl;

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

    auto now = std::chrono::system_clock::now();
    auto now_sec = std::chrono::floor<std::chrono::seconds>(now);


    int delta = 24; // using as a variable for delta between the now and maximum difference to the event.

    // implement an edit to change delta !

    for (const auto &ev:evenimente) {
        std::chrono::sys_seconds event_tp = std::chrono::sys_days{ev.getDate()} + ev.getHour().to_duration();

        if (event_tp > now_sec && event_tp - now_sec < std::chrono::hours(delta)) {
            std::cout << "Upcoming event: " << ev.getTitle() << " at "
                      << unsigned(ev.getHour().hours().count()) << ":"
                      << unsigned(ev.getHour().minutes().count()) << ":"
                      << unsigned(ev.getHour().seconds().count())
                      << " on "
                      << int(ev.getDate().year()) << "/"
                      << unsigned(ev.getDate().month()) << "/"
                      << unsigned(ev.getDate().day())
                      << " in " << ev.getLocation() << "\n";
        }
    }
    /*
    sys_days{ev.data} gives you midnight of the event’s day.
    ev.ora.to_duration() is the time since midnight.
    sys_seconds event_tp is the full timestamp for that event.
    event_tp > now_sec && event_tp - now_sec < hours(delta): Only shows events in the future and within 24 hours. */
}

void EventManager::saveToFile(const std::string &filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr<<"Error in opening "<<filename<<"."<<std::endl;
        return;
    }

    for (const auto & ev:evenimente) {
        fout<<ev.serialize();
        fout<<'\n';
    }

}

void EventManager::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr<<"Error in opening "<<filename<<"."<<std::endl;
        return;
    }

    evenimente.clear(); // reset list of events;
    std::string line;
    while (std::getline(fin, line))
        evenimente.push_back(Event::deserialize(line));

    fin.close();
}
