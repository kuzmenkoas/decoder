file(GLOB SOURCES src/*.cc)
file(GLOB HEADERS include/*.hh)

add_library(writer STATIC ${SOURCES} ${HEADERS})
target_include_directories(writer PUBLIC include)
target_link_libraries(writer PUBLIC config global ${ROOT_LIBRARIES})