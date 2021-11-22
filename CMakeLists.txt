cmake_minimum_required(VERSION 3.9.4)
set(CMAKE_CXX_STANDARD 17)
project(Analyzer)

add_subdirectory(Analyzer)
add_subdirectory(CommandManager)

set_target_properties(
    Analyzer
    PROPERTIES 
        OUTPUT_NAME "analyze"
)
