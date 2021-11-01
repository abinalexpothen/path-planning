project(PathPlanning)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/map.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/matplotlibcpp.h
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(bfs_pathplanning src/bfs_planner.cpp)
target_link_libraries(bfs_pathplanning)

add_executable(astar_pathplanning src/astar_planner.cpp)
target_link_libraries(astar_pathplanning)

add_executable(astar_real_pathplanning matplotlibcpp.h src/astar_realmap_sim.cpp ${PYTHON_LIBRARIES})
target_link_libraries(astar_real_pathplanning python2.7)