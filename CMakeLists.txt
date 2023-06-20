cmake_minimum_required(VERSION 3.25)
project(search_engine
        VERSION 0.1
        DESCRIPTION "Search engine"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

target_include_directories(BooleanIR PUBLIC
        include
        )

target_link_libraries(BooleanIRSimple PUBLIC
        BooleanIR)
