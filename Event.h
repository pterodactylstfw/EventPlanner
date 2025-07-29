//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <chrono>

class Event {
private:
    unsigned int id;

    std::string titlu;

    std::string descriere;

    std::chrono::year_month_day data;

    std::chrono::hh_mm_ss<std::chrono::seconds> ora;

    std::string locatie;

public:
    Event() = default;
    Event(unsigned int ID, const std::string & title, const std::string & description,
          const std::chrono::year_month_day& date, const std::chrono::hh_mm_ss<std::chrono::seconds>& hour,
          const std::string & location)
        : id(ID), titlu(title), descriere(description), data(date), ora(hour), locatie(location) {}


    unsigned int getID() const;
    void setID(unsigned int ID);

    std::string getTitle() const;
    void setTitle(const std::string & title);

    std::string getDescription() const;
    void setDescription(const std::string & description);

    std::chrono::year_month_day getDate() const;
    void setDate(const std::chrono::year_month_day& date);

    std::chrono::hh_mm_ss<std::chrono::seconds> getHour() const;
    void setHour(const std::chrono::hh_mm_ss<std::chrono::seconds>& hour);


    std::string getLocation() const;
    void setLocation(const std::string & location);

    void print() const;

    std::string toString() const;

    bool operator<(const Event &) const;

    std::string serialize() const;

    static Event deserialize(const std::string& line);

    ~Event() = default;
};



#endif //EVENT_H
