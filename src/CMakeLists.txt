cmake_minimum_required(VERSION 3.29)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(cpp_srcs
        GameEngine.cpp
        managers/StateManager.cpp
        interfaces/IState.cpp
)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG origin/master)
FetchContent_MakeAvailable(SFML)

add_library(Game-Engine ${cpp_srcs})
target_include_directories(Game-Engine PUBLIC ../include)
target_link_libraries(Game-Engine PUBLIC
        SFML::System
        SFML::Window
        SFML::Graphics
        )