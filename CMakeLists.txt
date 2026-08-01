cmake_minimum_required(VERSION 4.3)
project(game_of_life LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

# raylib parameters
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/raylib)

add_executable(game_of_life src/main.cpp src/grid.cpp src/graphics.cpp)

target_include_directories(game_of_life PRIVATE src/include)
target_include_directories(game_of_life PRIVATE libs/) # raygui.h

target_link_libraries(game_of_life PRIVATE raylib)

# unused

# Set the asset path macro to the absolute path on the dev machine
# target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# Set the asset path macro in release mode
# target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package")
