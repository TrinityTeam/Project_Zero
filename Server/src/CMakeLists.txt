project(GameServer)
cmake_minimum_required(VERSION 2.8)

set(SOURCES main Network/Server)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../../cmake)
find_package(SFML 2.4 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
include_directories(../..)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} pthread)
