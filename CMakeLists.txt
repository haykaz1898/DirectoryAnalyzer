cmake_minimum_required(VERSION 3.9.4)
set(CMAKE_CXX_STANDARD 17)
project(TensorTest VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(TensorTest
    Option.cpp
    OptionManager.cpp
    Command.cpp
    AnalyzeCommand.cpp
    CommandParser.cpp
    TensorTest.cpp
    )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set_target_properties(
    TensorTest
    PROPERTIES 
        OUTPUT_NAME "analyze"
)
include(CPack)
