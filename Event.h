//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#ifndef EVENT_H
#define EVENT_H
#include <string>


class Event {
private:
    unsigned int id;

    std::string titlu;
    std::string descriere;
    std::string data, ora;
    std::string locatie;

public:
    Event() = default;
    Event(unsigned int ID, const std::string & title, const std::string & description, const std::string &date, const std::string & hour, const std::string & location): id(ID), titlu(title),descriere(description),data(date), ora(hour), locatie(location) {}

    unsigned int getID() const;
    void setID(unsigned int ID);

    std::string getTitle() const;
    void setTitle(const std::string & title);

    std::string getDescription() const;
    void setDescription(const std::string & description);

    std::string getDate() const;
    void setDate(const std::string & date);

    std::string getHour() const;
    void setHour(const std::string & hour);

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
