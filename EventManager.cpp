//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#include "EventManager.h"
#include <fstream>

int EventManager::size() const {
    return evenimente.size();
}


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

std::vector<std::string> EventManager::showEvents() const {

    std::vector<std::string> events;
    if (evenimente.empty())
        events.push_back("Nu exista evenimente de afisat!");

    for (const auto &ev: evenimente) {
        events.push_back(ev.toString() + "-----");
    }

    return events;
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

std::vector<std::string> EventManager::notifyUpcomingEvents() const {
    auto now = std::chrono::system_clock::now();
    auto now_sec = std::chrono::floor<std::chrono::seconds>(now);

    int delta = 24; // ore

    std::vector<std::string> foundEvents;

    for (const auto &ev: evenimente) {
        std::chrono::sys_seconds event_tp = std::chrono::sys_days{ev.getDate()} + ev.getHour().to_duration() -
                                            std::chrono::hours(3); // -3 pt UTC, romania are GMT+3, hardcoded
        auto diff = event_tp - now_sec;

        // verif daca evenimentul e in <= delta ore
        if (event_tp >= now_sec && diff <= std::chrono::hours(delta)) {
            auto hours_left = std::chrono::duration_cast<std::chrono::hours>(diff).count();
            auto minutes_left = std::chrono::duration_cast<std::chrono::minutes>(diff).count() % 60;
            auto seconds_left = std::chrono::duration_cast<std::chrono::seconds>(diff).count() % 60;

            std::stringstream tmp;

            tmp << "Upcoming event: " << ev.getTitle()
                    << " at " << std::setw(2) << std::setfill('0') << unsigned(ev.getHour().hours().count())
                    << ":" << std::setw(2) << std::setfill('0') << unsigned(ev.getHour().minutes().count())
                    << ":" << std::setw(2) << std::setfill('0') << unsigned(ev.getHour().seconds().count())
                    << " on " << int(ev.getDate().year()) << "/"
                    << unsigned(ev.getDate().month()) << "/"
                    << unsigned(ev.getDate().day())
                    << " in " << ev.getLocation()
                    << " (in " << hours_left << "h "
                    << minutes_left << "m "
                    << seconds_left << "s)";
            foundEvents.push_back(tmp.str());
        }
    }
    if (foundEvents.empty())
        foundEvents.push_back("Nu exista evenimente in urmatoarele " + std::to_string(delta) + " ore.");

    return foundEvents;
}

void EventManager::saveToFile(const std::string &filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Error in opening " << filename << "." << std::endl;
        return;
    }

    for (const auto &ev: evenimente) {
        fout << ev.serialize();
        fout << '\n';
    }
}

void EventManager::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error in opening " << filename << "." << std::endl;
        return;
    }

    evenimente.clear(); // reset list of events;
    std::string line;
    while (std::getline(fin, line))
        evenimente.push_back(Event::deserialize(line));

    unsigned int maxID = 0;
    for (const auto &ev: evenimente)
        if (ev.getID() > maxID) maxID = ev.getID();
    currentID = maxID + 1;

    fin.close();
}
