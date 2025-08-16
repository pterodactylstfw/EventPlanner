//
// Created by Raul-Nicolae Constantin on 14.08.2025.
//

#include "crow_all.h"
#include "EventManager.h"
#include "Event.h"
#include <nlohmann/json.hpp>
#include <iomanip> // Necesar pentru std::setw si std::setfill

using json = nlohmann::json;

EventManager manager;

struct CorsMiddleware {
    struct context {};

    void before_handle(crow::request & req, crow::response & res, context& ctw) {
        if (req.method == crow::HTTPMethod::Options) {
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
            res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            res.code = 204;
            res.end();
        }
    }

        void after_handle(crow::request & req, crow::response & res, context & ctx) {
            res.add_header("Access-Control-Allow-Origin", "*");
        }
    };

Event eventFromJson(const crow::json::rvalue &json_body, unsigned int id) {
    std::string title = json_body["title"].s();
    std::string description = json_body["description"].s();
    std::string data_str = json_body["date"].s();
    std::string ora_str = json_body["hour"].s();
    std::string location = json_body["location"].s();

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
    // AICI ERA UN BUG: foloseai minutes in loc de seconds
    auto s = std::chrono::seconds{std::stoi(sec_str)};

    std::chrono::hh_mm_ss<std::chrono::seconds> ora{h + min + s};

    return {id, title, description, data, ora, location};
}


int main() {
    crow::App<CorsMiddleware> app;
    manager.loadFromFile("evenimente.txt");

    CROW_ROUTE(app, "/add-event").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid JSON");

        unsigned int newID = manager.getNextID();
        Event ev = eventFromJson(body, newID);
        manager.addEvent(ev);
        manager.saveToFile("evenimente.txt");
        return crow::response(200, "Eveniment adaugat cu succes!");
    });


    CROW_ROUTE(app, "/events").methods(crow::HTTPMethod::Get)([]() {
        json eventsArray = json::array();
        for (const auto &ev: manager.getEvents()) {
            json eventJson;
            eventJson["id"] = ev.getID();
            eventJson["title"] = ev.getTitle();
            eventJson["description"] = ev.getDescription();

            auto data = ev.getDate();
            std::stringstream date_ss;
            date_ss << std::setw(2) << std::setfill('0') << unsigned(data.day()) << "/"
                    << std::setw(2) << std::setfill('0') << unsigned(data.month()) << "/"
                    << int(data.year());
            eventJson["date"] = date_ss.str();

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

    // SINTAXA CORECTA: <int> in URL
    // ORDINEA CORECTA: (request, id) in lambda
    CROW_ROUTE(app, "/events/<int>").methods(crow::HTTPMethod::Put)
    ([](const crow::request &req, int id) {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid JSON");

        Event event = eventFromJson(body, id);
        bool ok = manager.editEvent(id, event);

        if (ok) {
            manager.saveToFile("evenimente.txt");
            return crow::response(200, "Eveniment editat cu succces!");
        } else
            return crow::response(404, "Evenimentul nu exista!");
    });

    // SINTAXA CORECTA: <int> in URL si doar `id` ca parametru
    CROW_ROUTE(app, "/events/<int>").methods(crow::HTTPMethod::Delete)
    ([](int id) {
        bool ok = manager.deleteEvent(id);
        if (ok) {
            manager.saveToFile("evenimente.txt");
            return crow::response(200, "Eveniment sters cu succes!");
        } else
            return crow::response(404, "Evenimentul nu exista!");
    });

    app.port(18080).multithreaded().run();
}