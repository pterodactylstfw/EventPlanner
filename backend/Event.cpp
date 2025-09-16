//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#include "Event.h"
#include "JsonUtils.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

unsigned int Event::getID() const {
    return id;
}

void Event::setID(unsigned int ID) {
    id = ID;
}

std::string Event::getTitle() const {
    return titlu;
}

void Event::setTitle(const std::string &title) {
    titlu = title;
}

std::string Event::getDescription() const {
    return descriere;
}

void Event::setDescription(const std::string &description) {
    descriere = description;
}

std::chrono::year_month_day Event::getDate() const {
    return data;
}

void Event::setDate(const std::chrono::year_month_day &date) {
    data = date;
}

std::chrono::hh_mm_ss<std::chrono::seconds> Event::getHour() const {
    return ora;
}

void Event::setHour(const std::chrono::hh_mm_ss<std::chrono::seconds> &hour) {
    ora = hour;
}

std::string Event::getLocation() const {
    return locatie;
}

void Event::setLocation(const std::string &location) {
    locatie = location;
}

std::string Event::toString() const {
    std::stringstream ss;
    ss << "Detalii eveniment " << titlu << ':' << '\n';
    ss << '\t' << "Descriere eveniment: " << descriere << '\n';
    ss << '\t' << "Data eveniment " << titlu << ':' << data << ", ora: " << ora << '\n';
    ss << '\t' << "Locatie eveniment: " << locatie << '\n';
    return ss.str();
}


std::string Event::serialize() const {
    json j_ev = ::serialize(*this);
    return j_ev.dump();
}

Event Event::deserialize(const std::string &line) {
    json j_ev = json::parse(line);
    return ::deserialize(j_ev);
}

