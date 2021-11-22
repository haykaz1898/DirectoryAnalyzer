cmake_minimum_required(VERSION 3.9.4)
set(CMAKE_CXX_STANDARD 17)
project(CommandManager VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/CommandManager/Headers)

add_library(CommandManager 
            Option.cpp
            OptionManager.cpp
            Command.cpp
            CommandParser.cpp)