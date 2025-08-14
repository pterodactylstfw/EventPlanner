cmake_minimum_required(VERSION 3.31)
project(EventPlanner)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "/opt/homebrew")
find_package(Boost REQUIRED)

set(CMAKE_PREFIX_PATH "/Users/pterodactylstfw/Qt/6.9.1/macos/lib/cmake")
include_directories(${CMAKE_SOURCE_DIR}/crow/include)

# Find Boost (folosește boost_system pentru Crow)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Find Asio
include_directories(/opt/homebrew/include)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(EventPlanner main.cpp
        Event.cpp
        Event.h
        EventManager.cpp
        EventManager.h)
add_executable(EventPlannerGui main_gui.cpp
        Event.cpp
        Event.h
        EventManager.cpp
        EventManager.h)


target_link_libraries(EventPlanner PRIVATE Qt6::Widgets)
target_link_libraries(EventPlannerGui PRIVATE Qt6::Widgets)
target_link_libraries(EventPlanner PRIVATE ${Boost_LIBRARIES} pthread)