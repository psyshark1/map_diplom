cmake_minimum_required (VERSION 3.8)

project (map_diplom)
set (CMAKE_CXX_STANDARD 17)

add_executable (map_diplom map_diplom.cpp thread_pool.h thread_pool.cpp safe_queue.cpp)

target_compile_features(map_diplom PRIVATE cxx_std_17)
