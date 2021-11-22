
include_directories(${PROJECT_SOURCE_DIR}/Analyzer/Headers)
include_directories(${PROJECT_SOURCE_DIR}/CommandManager/Headers)
link_directories(${PROJECT_SOURCE_DIR}/CommandManager/Sources)
add_executable(Analyzer main.cpp)