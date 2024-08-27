cmake_minimum_required(VERSION 3.29)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG origin/master)
FetchContent_MakeAvailable(SFML)

set(cpp_srcs
        Engine.cpp
        managers/StateManager.cpp
        interfaces/IState.cpp
)

add_library(NightEngine ${cpp_srcs})
target_include_directories(NightEngine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(NightEngine PUBLIC
        SFML::System
        SFML::Window
        SFML::Graphics
        )