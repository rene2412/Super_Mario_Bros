cmake_minimum_required(VERSION 3.10)
project(SuperMarioClone)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Raylib
find_package(raylib REQUIRED)

# Add source files
set(SOURCES
    main.cpp
    mario.cpp
    enemies.cpp
    load_map.cpp
    game.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib (and its dependencies)
target_link_libraries(${PROJECT_NAME} raylib)

# For Linux, link additional X11 dependencies if needed
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m pthread dl X11 Xrandr Xi Xxf86vm Xcursor GL)
endif()

