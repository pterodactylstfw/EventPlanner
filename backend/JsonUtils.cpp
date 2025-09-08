//
// Created by Raul-Nicolae Constantin on 08.09.2025.
//

#include "JsonUtils.h"
#include <iostream>

json serialize(const Event &ev) {
    json j_ev;
    j_ev["id"] = ev.getID();
    j_ev["titlu"] = ev.getTitle();
    j_ev["descriere"] = ev.getDescription();
    j_ev["locatie"] = ev.getLocation();


    // DATE PARSING FORMAT: YYYY-MM-DD

    unsigned int day = static_cast<unsigned int>(unsigned(ev.getDate().day()));
    unsigned int month = static_cast<unsigned int>(unsigned(ev.getDate().month()));
    int year = int(ev.getDate().year());

    std::stringstream date_str;
    date_str << std::setw(4)<<std::setfill('0')<<year << '-' << std::setw(2)<<std::setfill('0')<<month << '-' << std::setw(2)<<std::setfill('0')<<day;

    j_ev["data"] = date_str.str();

    // HOUR PARSING FORMAT: HH:mm:ss

    std::stringstream hour_str;
    hour_str << std::setw(2) << std::setfill('0') << ev.getHour().hours().count() << ':' << std::setw(2) << std::setfill('0') << ev.getHour().minutes().count() << ':' << std::setw(2) << std::setfill('0') << ev.getHour().seconds().count();

    j_ev["ora"] = hour_str.str();

    return j_ev;
}


Event deserialize(const json &j_ev) {
    std::vector<std::string> required = {"id", "titlu", "descriere", "locatie", "ora"};
    std::vector<std::string> missing;
    for (const auto& key : required) {
        if (!j_ev.contains(key)) missing.push_back(key);
    }
    // Data - either in parts or string
    bool hasDataString = j_ev.contains("data");
    bool hasDataParts = j_ev.contains("an") && j_ev.contains("luna") && j_ev.contains("zi");
    if (!hasDataString && !hasDataParts) missing.push_back("data");

    if (!missing.empty()) {
        std::cout << "Received JSON:\n" << j_ev.dump(4) << std::endl;
        std::string msg = "Incomplete JSON: missing keys ";
        for (size_t i = 0; i < missing.size(); ++i) {
            msg += missing[i];
            if (i != missing.size() - 1) msg += ", ";
        }
        throw std::invalid_argument(msg);
    }

    unsigned int id = j_ev["id"];
    std::string titlu = j_ev["titlu"];
    std::string descriere = j_ev["descriere"];
    std::string locatie = j_ev["locatie"];
    std::string ora_str = j_ev["ora"];

    std::chrono::year_month_day data;
    if (hasDataString) {
        std::string data_str = j_ev["data"];
        std::stringstream ss_data(data_str);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss_data, token, '-'))
            tokens.push_back(token);

        if (tokens.size() != 3)
            throw std::invalid_argument("Formatul datei este invalid! Așteptat: YYYY-MM-DD.");

        data = std::chrono::year_month_day{
            std::chrono::year{std::stoi(tokens[0])},
            std::chrono::month{static_cast<unsigned>(std::stoi(tokens[1]))},
            std::chrono::day{static_cast<unsigned>(std::stoi(tokens[2]))}
        };
    } else {
        data = std::chrono::year_month_day{
            std::chrono::year{j_ev["an"]},
            std::chrono::month{static_cast<unsigned>(j_ev["luna"])},
            std::chrono::day{static_cast<unsigned>(j_ev["zi"])}
        };
    }

    // Hour parsing: "HH:mm:ss"
    std::stringstream ss_ora(ora_str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss_ora, token, ':'))
        tokens.push_back(token);

    if (tokens.size() != 3)
        throw std::invalid_argument("Formatul orei este invalid! Așteptat: HH:mm:ss.");

    std::chrono::hours h{std::stoi(tokens[0])};
    std::chrono::minutes m{std::stoi(tokens[1])};
    std::chrono::seconds s{std::stoi(tokens[2])};

    auto total_seconds = h + m + s;
    std::chrono::hh_mm_ss<std::chrono::seconds> ora{total_seconds};

    return Event{id, titlu, descriere, data, ora, locatie};
}

