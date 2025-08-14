cmake_minimum_required(VERSION 3.16)
project(EventPlanner)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

# Include Crow library
include_directories(${CMAKE_SOURCE_DIR}/../crow_lib/include)

# CLI version (original)
add_executable(EventPlanner 
    main.cpp
    Event.cpp
    Event.h
    EventManager.cpp
    EventManager.h
)

# REST API version
add_executable(EventPlannerAPI 
    main_api.cpp
    Event.cpp
    Event.h
    EventManager.cpp
    EventManager.h
)

# Link libraries
target_link_libraries(EventPlanner PRIVATE ${Boost_LIBRARIES} pthread)
target_link_libraries(EventPlannerAPI PRIVATE ${Boost_LIBRARIES} ${JSONCPP_LIBRARIES} pthread)

# Include directories for JSON
target_include_directories(EventPlannerAPI PRIVATE ${JSONCPP_INCLUDE_DIRS})