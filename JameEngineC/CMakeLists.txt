cmake_minimum_required(VERSION 3.21)

project(JameEngineC VERSION 0.1.0 LANGUAGES C)

add_executable(JameEngineC source/main.c)

target_include_directories(JameEngineC PUBLIC SDL2/include)
target_link_directories(JameEngineC PUBLIC SDL2/lib/x64/)
target_link_libraries(JameEngineC SDL2)
target_link_libraries(JameEngineC SDL2main)