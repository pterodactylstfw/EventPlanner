#include "crow.h"
#include "EventManager.h"
#include "Event.h"
#include <json/json.h>
#include <sstream>
#include <iomanip>

// Global event manager instance
EventManager globalEventManager;

// Helper function to convert Event to JSON
Json::Value eventToJson(const Event& event) {
    Json::Value json;
    json["id"] = event.getID();
    json["title"] = event.getTitle();
    json["description"] = event.getDescription();
    json["location"] = event.getLocation();
    
    // Convert date to string
    auto date = event.getDate();
    std::ostringstream dateStr;
    dateStr << std::setw(2) << std::setfill('0') << unsigned(date.day()) << "/"
            << std::setw(2) << std::setfill('0') << unsigned(date.month()) << "/"
            << int(date.year());
    json["date"] = dateStr.str();
    
    // Convert time to string
    auto hour = event.getHour();
    std::ostringstream timeStr;
    timeStr << std::setw(2) << std::setfill('0') << hour.hours().count() << ":"
            << std::setw(2) << std::setfill('0') << hour.minutes().count() << ":"
            << std::setw(2) << std::setfill('0') << hour.seconds().count();
    json["time"] = timeStr.str();
    
    return json;
}

// Helper function to parse date string to chrono::year_month_day
std::chrono::year_month_day parseDate(const std::string& dateStr) {
    std::stringstream ss(dateStr);
    std::string day_str, month_str, year_str;
    
    std::getline(ss, day_str, '/');
    std::getline(ss, month_str, '/');
    std::getline(ss, year_str);
    
    return std::chrono::year_month_day{
        std::chrono::year{std::stoi(year_str)},
        std::chrono::month{static_cast<unsigned int>(std::stoul(month_str))},
        std::chrono::day{static_cast<unsigned int>(std::stoul(day_str))}
    };
}

// Helper function to parse time string to chrono::hh_mm_ss
std::chrono::hh_mm_ss<std::chrono::seconds> parseTime(const std::string& timeStr) {
    std::stringstream ss(timeStr);
    std::string hour_str, min_str, sec_str;
    
    std::getline(ss, hour_str, ':');
    std::getline(ss, min_str, ':');
    std::getline(ss, sec_str);
    
    auto h = std::chrono::hours{std::stol(hour_str)};
    auto min = std::chrono::minutes{std::stol(min_str)};
    auto s = std::chrono::seconds{std::stol(sec_str.empty() ? "0" : sec_str)};
    
    return std::chrono::hh_mm_ss<std::chrono::seconds>{h + min + s};
}

int main() {
    crow::SimpleApp app;
    
    // Enable CORS for Angular frontend
    app.loglevel(crow::LogLevel::Info);
    
    // Middleware to handle CORS (simplified - we'll add CORS headers to each response instead)
    
    // GET /api/events - Get all events
    CROW_ROUTE(app, "/api/events").methods("GET"_method)
    ([&](const crow::request& req) {
        auto events = globalEventManager.getEvents();
        Json::Value jsonArray(Json::arrayValue);
        
        for (const auto& event : events) {
            jsonArray.append(eventToJson(event));
        }
        
        Json::StreamWriterBuilder builder;
        std::string jsonString = Json::writeString(builder, jsonArray);
        
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Content-Type", "application/json");
        res.write(jsonString);
        return res;
    });
    
    // GET /api/events/{id} - Get event by ID
    CROW_ROUTE(app, "/api/events/<int>").methods("GET"_method)
    ([&](const crow::request& req, int id) {
        auto event = globalEventManager.findEventByID(id);
        if (event == nullptr) {
            crow::response res(404);
            res.add_header("Access-Control-Allow-Origin", "*");
            res.write("{\"error\": \"Event not found\"}");
            return res;
        }
        
        Json::Value json = eventToJson(*event);
        Json::StreamWriterBuilder builder;
        std::string jsonString = Json::writeString(builder, json);
        
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Content-Type", "application/json");
        res.write(jsonString);
        return res;
    });
    
    // POST /api/events - Create new event
    CROW_ROUTE(app, "/api/events").methods("POST"_method)
    ([&](const crow::request& req) {
        try {
            Json::Value json;
            Json::Reader reader;
            
            if (!reader.parse(req.body, json)) {
                crow::response res(400);
                res.add_header("Access-Control-Allow-Origin", "*");
                res.write("{\"error\": \"Invalid JSON\"}");
                return res;
            }
            
            // Create new event
            unsigned int id = globalEventManager.getNextID();
            std::string title = json["title"].asString();
            std::string description = json["description"].asString();
            std::string location = json["location"].asString();
            auto date = parseDate(json["date"].asString());
            auto time = parseTime(json["time"].asString());
            
            Event newEvent(id, title, description, date, time, location);
            globalEventManager.addEvent(newEvent);
            
            Json::Value responseJson = eventToJson(newEvent);
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, responseJson);
            
            crow::response res(201);
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Content-Type", "application/json");
            res.write(jsonString);
            return res;
            
        } catch (const std::exception& e) {
            crow::response res(400);
            res.add_header("Access-Control-Allow-Origin", "*");
            res.write("{\"error\": \"" + std::string(e.what()) + "\"}");
            return res;
        }
    });
    
    // PUT /api/events/{id} - Update event
    CROW_ROUTE(app, "/api/events/<int>").methods("PUT"_method)
    ([&](const crow::request& req, int id) {
        try {
            Json::Value json;
            Json::Reader reader;
            
            if (!reader.parse(req.body, json)) {
                crow::response res(400);
                res.add_header("Access-Control-Allow-Origin", "*");
                res.write("{\"error\": \"Invalid JSON\"}");
                return res;
            }
            
            std::string title = json["title"].asString();
            std::string description = json["description"].asString();
            std::string location = json["location"].asString();
            auto date = parseDate(json["date"].asString());
            auto time = parseTime(json["time"].asString());
            
            Event updatedEvent(id, title, description, date, time, location);
            
            if (!globalEventManager.editEvent(id, updatedEvent)) {
                crow::response res(404);
                res.add_header("Access-Control-Allow-Origin", "*");
                res.write("{\"error\": \"Event not found\"}");
                return res;
            }
            
            Json::Value responseJson = eventToJson(updatedEvent);
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, responseJson);
            
            crow::response res;
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Content-Type", "application/json");
            res.write(jsonString);
            return res;
            
        } catch (const std::exception& e) {
            crow::response res(400);
            res.add_header("Access-Control-Allow-Origin", "*");
            res.write("{\"error\": \"" + std::string(e.what()) + "\"}");
            return res;
        }
    });
    
    // DELETE /api/events/{id} - Delete event
    CROW_ROUTE(app, "/api/events/<int>").methods("DELETE"_method)
    ([&](const crow::request& req, int id) {
        if (!globalEventManager.deleteEvent(id)) {
            crow::response res(404);
            res.add_header("Access-Control-Allow-Origin", "*");
            res.write("{\"error\": \"Event not found\"}");
            return res;
        }
        
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.write("{\"message\": \"Event deleted successfully\"}");
        return res;
    });
    
    // OPTIONS for all routes (CORS preflight)
    CROW_ROUTE(app, "/api/events").methods("OPTIONS"_method)
    ([](const crow::request& req) {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        return res;
    });
    
    std::cout << "🚀 Event Planner REST API Server starting on port 8080..." << std::endl;
    std::cout << "📋 Available endpoints:" << std::endl;
    std::cout << "  GET    /api/events       - Get all events" << std::endl;
    std::cout << "  GET    /api/events/{id}  - Get event by ID" << std::endl;
    std::cout << "  POST   /api/events       - Create new event" << std::endl;
    std::cout << "  PUT    /api/events/{id}  - Update event" << std::endl;
    std::cout << "  DELETE /api/events/{id}  - Delete event" << std::endl;
    
    app.port(8080).multithreaded().run();
    
    return 0;
}