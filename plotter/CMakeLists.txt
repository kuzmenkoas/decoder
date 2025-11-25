file(GLOB SOURCES src/*.cc)
file(GLOB HEADERS include/*.hh)

add_library(plotter STATIC ${SOURCES} ${HEADERS})
target_include_directories(plotter PUBLIC include)
target_link_libraries(plotter PUBLIC config global writer ${ROOT_LIBRARIES})