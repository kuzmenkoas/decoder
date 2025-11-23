file(GLOB SOURCES src/*.cc)
file(GLOB HEADERS include/*.hh)

add_library(config STATIC ${SOURCES} ${HEADERS})
target_include_directories(config PUBLIC include)
target_link_libraries(config PUBLIC global ${ROOT_LIBRARIES})