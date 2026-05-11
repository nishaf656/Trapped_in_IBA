cmake_minimum_required(VERSION 3.16)
project(TrappedInIBA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# point to sfml
set(SFML_DIR "C:/SFML/SFML-3.1.0/lib/cmake/SFML")

# all the cpp files
set(SOURCES
src/main.cpp
src/core/GameManager.cpp
src/core/ChoiceManager.cpp
src/core/AssetManager.cpp
src/player/Player.cpp
src/clues/Clue.cpp
src/interactables/Interactable.cpp
src/interactables/Book.cpp
src/interactables/Computer.cpp
src/interactables/NoticeBoard.cpp
src/interactables/EnergyItem.cpp
src/locations/Location.cpp
src/locations/Library.cpp
src/locations/Classroom.cpp
src/locations/ComputerLab.cpp
src/locations/Cafeteria.cpp
src/locations/CampusMap.cpp
)

add_executable(TrappedInIBA ${SOURCES})

# link sfml libs
find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Window System)
target_link_libraries(TrappedInIBA PRIVATE SFML::Graphics SFML::Window SFML::System)

# where to look for headers
target_include_directories(TrappedInIBA PRIVATE
src
C:/SFML/SFML-3.1.0/include
)

# move assets to build folder
add_custom_command(TARGET TrappedInIBA POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"${CMAKE_SOURCE_DIR}/assets"
"$<TARGET_FILE_DIR:TrappedInIBA>/assets"
COMMENT "copying assets"
)