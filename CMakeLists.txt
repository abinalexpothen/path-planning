project(PathPlanning)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

add_executable(bfs_pathplanning src/breadth_first_search.cpp)
target_link_libraries(bfs_pathplanning)

add_executable(astar_pathplanning src/a_star.cpp)
target_link_libraries(astar_pathplanning)