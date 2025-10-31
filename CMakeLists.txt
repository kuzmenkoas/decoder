cmake_minimum_required(VERSION 3.16...3.27)
project(decoder)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(decoder decoder.cc ${sources} ${headers})
target_include_directories(decoder PRIVATE include)
target_link_libraries(decoder ${ROOT_LIBRARIES})