cmake_minimum_required(VERSION 3.17.3)

project(cpp-gol)

add_executable(${PROJECT_NAME} ./main.cpp ./src/GameOfLife.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)