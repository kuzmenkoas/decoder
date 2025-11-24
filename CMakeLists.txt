cmake_minimum_required(VERSION 3.16...3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(decoder)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

add_subdirectory(global)
add_subdirectory(config)
add_subdirectory(writer)
add_subdirectory(plotter)
add_subdirectory(decoders)

add_executable(decoder decoder.cc)

target_link_libraries(decoder PRIVATE 
    decoders
    plotter
    writer
    config
    global
    ${ROOT_LIBRARIES}
)