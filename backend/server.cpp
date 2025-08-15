//
// Created by Raul-Nicolae Constantin on 14.08.2025.
//

#include "crow_all.h"
#include "EventManager.h"
#include "Event.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

EventManager manager;


Event eventFromJson(const crow::json::rvalue &json, unsigned int id) {
    std::string title = json["title"].s();
    std::string description = json["description"].s();
    std::string data_str = json["date"].s();
    std::string ora_str = json["hour"].s();
    std::string location = json["location"].s();

    std::stringstream data_ss(data_str);
    std::string day_str, month_str, year_str;

    std::getline(data_ss, day_str, '/');
    std::getline(data_ss, month_str, '/');
    std::getline(data_ss, year_str);

    auto y = std::chrono::year{std::stoi(year_str)};
    auto m = std::chrono::month{static_cast<unsigned int>(std::stoul(month_str))};
    auto d = std::chrono::day{static_cast<unsigned int>(std::stoul(day_str))};

    std::chrono::year_month_day data{y, m, d};

    std::stringstream ora_ss(ora_str);
    std::string hour_str, min_str, sec_str;

    std::getline(ora_ss, hour_str, ':');
    std::getline(ora_ss, min_str, ':');
    std::getline(ora_ss, sec_str);

    auto h = std::chrono::hours{std::stoi(hour_str)};
    auto min = std::chrono::minutes{std::stoi(min_str)};
    auto s = std::chrono::minutes{std::stoi(sec_str)};

    std::chrono::hh_mm_ss<std::chrono::seconds> ora{h + min + s};

    return {id, title, description, data, ora, location};
}


int main() {
    crow::SimpleApp app;
    manager.loadFromFile("evenimente.txt");

    CROW_ROUTE(app, "/add-event").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid JSON");

        unsigned int newID = manager.getNextID();

        Event ev = eventFromJson(body, newID);

        manager.addEvent(ev);

        manager.saveToFile("evenimente.txt"); // automatic save

        return crow::response(200, "Eveniment adaugat cu succes!");
    });


    CROW_ROUTE(app, "/events").methods(crow::HTTPMethod::Get)([]() {
        json eventsArray = json::array();

        for (const auto &ev: manager.getEvents()) {
            json eventJson;
            eventJson["id"] = ev.getID();
            eventJson["title"] = ev.getTitle();
            eventJson["description"] = ev.getDescription();

            // Format data cu stringstream
            auto data = ev.getDate();
            std::stringstream date_ss;
            date_ss << std::setw(2) << std::setfill('0') << unsigned(data.day()) << "/"
                    << std::setw(2) << std::setfill('0') << unsigned(data.month()) << "/"
                    << int(data.year());
            eventJson["date"] = date_ss.str();

            // Format ora cu stringstream
            auto ora = ev.getHour();
            std::stringstream ora_ss;
            ora_ss << std::setw(2) << std::setfill('0') << ora.hours().count() << ":"
                    << std::setw(2) << std::setfill('0') << ora.minutes().count() << ":"
                    << std::setw(2) << std::setfill('0') << ora.seconds().count();
            eventJson["hour"] = ora_ss.str();

            eventJson["location"] = ev.getLocation();

            eventsArray.push_back(eventJson);
        }

        return crow::response(eventsArray.dump());
    });


    CROW_ROUTE(app, "/events/{id}").methods(crow::HTTPMethod::Put)([](int id, const crow::request &req) {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid JSON");

        Event event = eventFromJson(body, id);
        bool ok = manager.editEvent(id, event);

        if (ok) {
            manager.saveToFile("evenimente.txt"); // automatic save
            return crow::response(200, "Eveniment editat cu succces!");
        } else
            return crow::response(404, "Evenimentul nu exista!");
    });

    CROW_ROUTE(app, "/events/{id}").methods(crow::HTTPMethod::Delete)([](int id) {
        bool ok = manager.deleteEvent(id);
        if (ok) {
            manager.saveToFile("evenimente.txt"); // automatic save
            return crow::response(200, "Eveniment sters cu succes!");
        } else
            return crow::response(404, "Evenimentul nu exista!");
    });

    app.port(18080).multithreaded().run();
}
