//
// Created by Raul-Nicolae Constantin on 29.07.2025.
//

#include "Event.h"

#include <chrono>
#include <iostream>

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

std::string Event::getDate() const {
    return data;
}

void Event::setDate(const std::string &date) {
    data = date;
}

std::string Event::getHour() const {
    return ora;
}

void Event::setHour(const std::string &hour) {
    ora = hour;
}

std::string Event::getLocation() const {
    return locatie;
}

void Event::setLocation(const std::string &location) {
    locatie = location;
}

void Event::print() const {
    std::cout<<"Detalii eveniment "<<titlu<<':'<<std::endl;
    std::cout<<'\t'<<"Descriere eveniment: "<<descriere<<std::endl;
    std::cout<<'\t'<<"Data eveniment "<<titlu<<':'<<data<<", ora: "<<ora<<std::endl;
    std::cout<<'\t'<<"Locatie eveniment: "<<locatie<<std::endl;
}

std::string Event::toString() const {
    std::string str = "Detalii eveniment " + titlu + ':'+'\n'+ '\t'+ "Descriere eveniment: "+ descriere + '\n' +'\t' + "Data eveniment " + titlu + ':' + data + ", ora: " + ora + '\n' + '\t' + "Locatie eveniment: " + locatie + '\n';
    return str;
}

bool Event::operator<(const Event &oth) const {
    if (this->data == oth.data)
        return this->ora < oth.ora;
    return this->data < oth.data;
}

std::string Event::serialize() const {
    return std::to_string(id) + "|" + titlu + "|" + descriere + "|" + data + "|" + ora + "|" +  locatie;;
}

Event Event::deserialize(const std::string &line) {
    std::stringstream ss(line);
    std::string part;
    std::vector<std::string> fields;

    while (std::getline(ss, part, '|')) fields.push_back(part);

    int id = std::stoi(fields[0]);
    std::string titlu = fields[1];
    std::string descriere = fields[2];
    std::string data = fields[3];
    std::string ora = fields[4];
    std::string locatie = fields[5];

    return Event(id, titlu, descriere, data, ora, locatie);
}
