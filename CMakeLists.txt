project(PathPlanning)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/map.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(bfs_pathplanning src/bfs_planner.cpp)
target_link_libraries(bfs_pathplanning)

add_executable(astar_pathplanning src/astar_planner.cpp)
target_link_libraries(astar_pathplanning)

add_executable(astar_real_pathplanning src/astar_realmap_sim.cpp)
target_link_libraries(astar_real_pathplanning)