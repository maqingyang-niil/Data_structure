cmake_minimum_required(VERSION 3.28)
project(data_structure)

set(CMAKE_CXX_STANDARD 17)

add_executable(data_structure main.cpp
        Binary_heap.cpp
        Leftist_heap.cpp
        map.cpp
        disjoint_set.cpp
        test.cpp
        adjacent_matrix_map.cpp
)
