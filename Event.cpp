//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#include "Event.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

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

void Event::print() const {
    std::cout << "Detalii eveniment " << titlu << " cu ID "<< id << ':' << std::endl;
    std::cout << '\t' << "Descriere eveniment: " << descriere << std::endl;
    // Folosim operatorul << supraîncărcat pentru tipurile chrono
    std::cout << '\t' << "Data eveniment " << titlu << ": " << data << ", ora: " << ora << std::endl;
    std::cout << '\t' << "Locatie eveniment: " << locatie << std::endl;
}

std::string Event::toString() const {
    std::stringstream ss;
    ss << "Detalii eveniment " << titlu << ':' << '\n';
    ss << '\t' << "Descriere eveniment: " << descriere << '\n';
    ss << '\t' << "Data eveniment " << titlu << ':' << data << ", ora: " << ora << '\n';
    ss << '\t' << "Locatie eveniment: " << locatie << '\n';
    return ss.str();
}

bool Event::operator<(const Event &other) const {
    // Combinăm data și ora într-un time_point pentru o comparație corectă
    auto this_time_point = std::chrono::sys_days(this->data) + this->ora.to_duration();
    auto other_time_point = std::chrono::sys_days(other.data) + other.ora.to_duration();

    return this_time_point < other_time_point;
}
std::string Event::serialize() const {
    std::stringstream ss;
    // Presupunem că data este de tip std::chrono::year_month_day
    // Extragem ziua, luna și anul
    unsigned int zi = static_cast<unsigned int>(unsigned(data.day()));
    unsigned int luna = static_cast<unsigned int>(unsigned(data.month()));
    int an = int(data.year());

    // FORMATARE: dd/mm/yyyy
    ss << id << "|"
       << titlu << "|"
       << descriere << "|"
       << (zi < 10 ? "0" : "") << zi << "/"
       << (luna < 10 ? "0" : "") << luna << "/"
       << an << "|"
       << ora << "|"
       << locatie;

    return ss.str();
}

Event Event::deserialize(const std::string &line) {
    std::stringstream line_ss(line);
    std::string part;
    std::vector<std::string> fields;

    while (std::getline(line_ss, part, '|')) {
        fields.push_back(part);
    }

    unsigned int id = std::stoul(fields[0]);
    std::string titlu = fields[1];
    std::string descriere = fields[2];
    std::string locatie = fields[5];

    std::stringstream data_ss(fields[3]);
    std::string year_str, month_str, day_str;

    std::getline(data_ss, day_str, '/');
    std::getline(data_ss, month_str, '/');
    std::getline(data_ss, year_str);

    auto y = std::chrono::year{std::stoi(year_str)};
    auto m = std::chrono::month{static_cast<unsigned int>(std::stoul(month_str))};
    auto d = std::chrono::day{static_cast<unsigned int>(std::stoul(day_str))};
    std::chrono::year_month_day parsed_data{y, m, d};

    std::stringstream ora_ss(fields[4]);
    std::string hour_str, min_str, sec_str;

    std::getline(ora_ss, hour_str, ':');
    std::getline(ora_ss, min_str, ':');
    std::getline(ora_ss, sec_str);

    auto h = std::chrono::hours{std::stol(hour_str)};
    auto min = std::chrono::minutes{std::stol(min_str)};
    auto s = std::chrono::seconds{std::stol(sec_str)};
    std::chrono::hh_mm_ss<std::chrono::seconds> parsed_ora{h + min + s};

    return {id, titlu, descriere, parsed_data, parsed_ora, locatie};
}


