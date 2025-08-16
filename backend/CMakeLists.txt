cmake_minimum_required(VERSION 3.31)
project(EventPlanner)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "/opt/homebrew")
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/crow/include)

# nlohmann-json
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# CLI
add_executable(EventPlanner
        main.cpp
        Event.cpp
        Event.h
        EventManager.cpp
        EventManager.h
)

# GUI
add_executable(EventPlannerGui
        main_gui.cpp
        Event.cpp
        Event.h
        EventManager.cpp
        EventManager.h
)

# API (Crow REST API)
add_executable(EventPlannerApi
        server.cpp
        Event.cpp
        Event.h
        EventManager.cpp
        EventManager.h
)

target_link_libraries(EventPlanner PRIVATE nlohmann_json::nlohmann_json ${Boost_LIBRARIES} pthread)
target_link_libraries(EventPlannerGui PRIVATE nlohmann_json::nlohmann_json ${Boost_LIBRARIES} pthread)
target_link_libraries(EventPlannerApi PRIVATE nlohmann_json::nlohmann_json ${Boost_LIBRARIES} pthread)