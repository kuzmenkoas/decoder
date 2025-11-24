file(GLOB SOURCES src/*.cc)
file(GLOB HEADERS include/*.hh)

if(NOT SOURCES)
    message(WARNING "No source files found in global/src/")
    set(SOURCES ${CMAKE_CURRENT_BINARY_DIR}/empty.cc)
    file(WRITE ${SOURCES} "// Empty source file\n")
endif()

add_library(global STATIC ${SOURCES} ${HEADERS})
target_include_directories(global PUBLIC include)
target_link_libraries(global ${ROOT_LIBRARIES})