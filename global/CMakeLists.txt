file(GLOB SOURCES src/*.cc)
file(GLOB HEADERS include/*.hh)

add_library(global STATIC ${SOURCES} ${HEADERS})
target_include_directories(global PUBLIC include)
target_link_libraries(global ${ROOT_LIBRARIES})