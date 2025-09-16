cmake_minimum_required(VERSION 3.31)
project(EventPlanner)

set(CMAKE_CXX_STANDARD 20)


set(CROW_HEADER_URL "https://github.com/CrowCpp/Crow/releases/latest/download/crow_all.h")
set(CROW_HEADER_PATH "${CMAKE_BINARY_DIR}/crow_all.h")

if(NOT EXISTS ${CROW_HEADER_PATH})
    file(DOWNLOAD ${CROW_HEADER_URL} ${CROW_HEADER_PATH} SHOW_PROGRESS)
endif()

include_directories(${CMAKE_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/crow/include)
include_directories(${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include)


# nlohmann-json
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

# asio - boost
FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-28-0
)
FetchContent_MakeAvailable(asio)

# CLI
add_executable(EventPlanner
        main.cpp
        Event.cpp
        Event.h
        EventManager.cpp
        EventManager.h
        JsonUtils.cpp
        JsonUtils.h
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
        JsonUtils.cpp
        JsonUtils.h
)

target_link_libraries(EventPlanner PRIVATE nlohmann_json::nlohmann_json pthread)
target_link_libraries(EventPlannerGui PRIVATE nlohmann_json::nlohmann_json pthread)
target_link_libraries(EventPlannerApi PRIVATE nlohmann_json::nlohmann_json pthread)