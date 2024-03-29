    cmake_minimum_required(VERSION 3.7)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    add_definitions(-std=c++17)

    set(CXX_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

    project(SDL2Test)

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS} src)
    find_package(SDL2_TTF REQUIRED)
    include_directories(${SDL2_TTF_INCLUDE_DIRS} src)
    message(STATUS "SDL2 include directory: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2_ttf include directory: ${SDL2_TTF_INCLUDE_DIRS}")


    add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/welcomescreen.cpp src/highscoremanager.cpp)
    string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
    target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
